#include "Instance.h"
#include "Core/Defines.h"
#include "DebugReportCallback.h"

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
//        "VK_LAYER_LUNARG_parameter_validation",
//        "VK_LAYER_LUNARG_vktrace",
//        "VK_LAYER_LUNARG_core_validation",
//        "VK_LAYER_LUNARG_screenshot",
//        "VK_LAYER_LUNARG_swapchain",
//        "VK_LAYER_LUNARG_object_tracker",
//        "VK_LAYER_GOOGLE_unique_objects",
//        "VK_LAYER_GOOGLE_threading",
//        "VK_LAYER_LUNARG_standard_validation"
    };

#ifdef OS_WIN
    enabledExtensions = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",
        "VK_EXT_debug_report"
    };
#elif OS_LINUX
    enabledExtensions = {
        "VK_KHR_surface",
        "VK_KHR_xcb_surface",
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
        debugCallback = std::make_unique<DebugReportCallback>(this);
        debugCallback->create();
    }
}

void Instance::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyInstance(handle, nullptr))
}

void Instance::setEnabledLayers(const std::vector<const char*> enabledLayers) {
    this->enabledLayers = enabledLayers;
}

void Instance::dumpLayers() {
    for (const auto& layer : layers) {
        PRINT(layer.layerName << " - " << layer.description
              << " (spec. ver. " << apiToString(layer.specVersion)
              << ", impl. ver. " << layer.implementationVersion << ")");
    }
}

void Instance::setEnabledExtensions(const std::vector<const char*> enabledExtensions) {
    this->enabledExtensions = enabledExtensions;
}

void Instance::dumpExtensions() {
    for (const auto& extension : extensions) {
        PRINT(extension.extensionName << " (spec. ver. " << extension.specVersion << ")");
    }
}

std::string Instance::apiToString(int api) {
    int major = (api >> 22) & 0x3FF;
    int minor = (api >> 12) & 0x3FF;
    int patch = api & 0xFFF;
    return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}
