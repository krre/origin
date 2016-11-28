#include "Instance.h"

using namespace Vulkan;

Instance::Instance() {
    // Get layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    layers.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

    enabledLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    // Get extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    extensions.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    for (const auto& extension : extensions) {
        enabledExtensions.push_back(extension.extensionName);
    }

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Application name";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.pEngineName = "Engine name";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = nullptr;

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &appInfo;
}

void Instance::create() {
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = enabledLayers.size();
        createInfo.ppEnabledLayerNames = enabledLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();

    checkError(vkCreateInstance(&createInfo, nullptr, &handle));
}
void Instance::setEnabledLayers(const std::vector<const char*> enabledLayers) {
    this->enabledLayers = enabledLayers;
}

void Instance::dumpLayers() {
    for (const auto& layer : layers) {
        print(layer.layerName);
    }
}

void Instance::setEnabledExtensions(const std::vector<const char*> enabledExtensions) {
    this->enabledExtensions = enabledExtensions;
}

void Instance::dumpExtensions() {
    for (const auto& extension : extensions) {
        print(extension.extensionName);
    }
}

Instance::~Instance() {
    vkDestroyInstance(handle, nullptr);
}
