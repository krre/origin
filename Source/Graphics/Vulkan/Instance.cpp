#include "Instance.h"
#include "Device/PhysicalDevice.h"
#include "Device/PhysicalDevices.h"
#include "Device/Device.h"
#include "Surface.h"
#include "Swapchain.h"
#include "Command/CommandPool.h"
#include "../../Core/App.h"
#include "../../Event/Event.h"
#include "../../Scene/SceneManager.h"

using namespace Vulkan;

Instance::Instance() {
    // Get layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    layers.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    // Get extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    extensions.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    enabledLayers = {
//        "VK_LAYER_LUNARG_api_dump",
        "VK_LAYER_LUNARG_parameter_validation",
//        "VK_LAYER_LUNARG_vktrace",
        "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_LUNARG_screenshot",
        "VK_LAYER_LUNARG_swapchain",
        "VK_LAYER_LUNARG_object_tracker",
        "VK_LAYER_GOOGLE_unique_objects",
        "VK_LAYER_GOOGLE_threading",
        "VK_LAYER_LUNARG_standard_validation"
    };

#ifdef __linux__
    enabledExtensions = {
        "VK_KHR_surface",
        "VK_KHR_xcb_surface",
        "VK_EXT_debug_report"
    };
#elif _WIN32
    enabledExtensions = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",
        "VK_EXT_debug_report"
    };
#endif

    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Application";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;
}

Instance::~Instance() {
    commandPool.reset();
    surface.reset();
    devices.clear();
    physicalDevices.reset();
    debugCallback.reset();
    destroy();
}

void Instance::create() {
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = enabledLayers.size();
        createInfo.ppEnabledLayerNames = enabledLayers.data();
    }
    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();

    VULKAN_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &handle), "Failed to create instance");

    if (enableValidationLayers) {
        debugCallback = std::make_shared<DebugReportCallback>(handle);
        debugCallback->create();
    }

    physicalDevices = std::make_shared<PhysicalDevices>(handle);
    PhysicalDevice* defaultPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (defaultPhysicalDevice == nullptr) {
        defaultPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsFamily = defaultPhysicalDevice->findQueue(VK_QUEUE_GRAPHICS_BIT);

    std::shared_ptr<Device> device = std::make_shared<Device>(defaultPhysicalDevice);
    devices.push_back(device);
    device->addQueueCreateInfo(graphicsFamily, { 1.0 });
    device->create();

    defaultDevice = device.get();

    surface = std::make_shared<Surface>(handle, defaultPhysicalDevice->getHandle());
    surface->create();

    commandPool = std::make_shared<CommandPool>(graphicsFamily);
    commandPool->create();

    Event::get()->windowResize.connect<Instance, &Instance::onWindowResize>(this);
}

void Instance::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyInstance(handle, nullptr))
}
void Instance::setEnabledLayers(const std::vector<const char*> enabledLayers) {
    this->enabledLayers = enabledLayers;
}

void Instance::dumpLayers() {
    for (const auto& layer : layers) {
        PRINT(layer.layerName);
    }
}

void Instance::setEnabledExtensions(const std::vector<const char*> enabledExtensions) {
    this->enabledExtensions = enabledExtensions;
}

void Instance::dumpExtensions() {
    for (const auto& extension : extensions) {
        PRINT(extension.extensionName);
    }
}

void Instance::setDefaultDevice(Device* device) {
    defaultDevice = device;
}

void Instance::onWindowResize(int width, int height) {
    if (App::get()->getIsRunning()) {
        defaultDevice->waitIdle();
        surface->getSwapchain()->rebuild();
        commandPool->reset();
        SceneManager::get()->rebuild();
    }
}
