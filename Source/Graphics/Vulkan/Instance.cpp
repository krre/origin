#include "Instance.h"

using namespace Vulkan;

Instance::Instance() {
    // Get layers
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    layers.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());
    std::vector<const char*> layerNames;
    print("Layers:")
    for (const auto& layer : layers) {
        print(layer.layerName);
        layerNames.push_back(layer.layerName);
    }
    print("")

    const std::vector<const char*> enabledLayers = {
//        "VK_LAYER_LUNARG_api_dump",
        "VK_LAYER_LUNARG_image",
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

    // Get extensions
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    extensions.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    std::vector<const char*> extNames;
    print("Extensions:")
    for (const auto& extension : extensions) {
        print(extension.extensionName);
        extNames.push_back(extension.extensionName);
    }
    print("")

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Gagarin";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.pEngineName = "Gagarin Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = nullptr;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &appInfo;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = enabledLayers.size();
        createInfo.ppEnabledLayerNames = enabledLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extNames.data();

    result = vkCreateInstance(&createInfo, nullptr, &handle);
}

Instance::~Instance() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyInstance(handle, nullptr);
    }
}
