#include "Instance.h"
#include "Core/Defines.h"
#include "DebugReportCallback.h"

using namespace Vulkan;

Instance::Instance() {
    // Get layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    layersProperties.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layersProperties.data());

    // Get extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    extensionProperties.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());

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
    std::vector<const char*> layers;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = enabledLayers.size();
        for (const auto& layer : enabledLayers) {
            layers.push_back(const_cast<char*>(layer.c_str()));
        }
        createInfo.ppEnabledLayerNames = layers.data();
    }

    createInfo.enabledExtensionCount = enabledExtensions.size();
    std::vector<const char*> extensions;
    for (const auto& extension : enabledExtensions) {
        extensions.push_back(const_cast<char*>(extension.c_str()));
    }
    createInfo.ppEnabledExtensionNames = extensions.data();

    VULKAN_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &handle), "Failed to create instance");

    if (enableValidationLayers) {
        debugCallback = std::make_unique<DebugReportCallback>(this);
        debugCallback->create();
    }
}

void Instance::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyInstance(handle, nullptr))
}

void Instance::setEnabledLayers(const std::vector<std::string> enabledLayers) {
    this->enabledLayers = enabledLayers;
}

void Instance::dumpLayers() {
    for (const auto& layer : layersProperties) {
        PRINT(layer.layerName << " - " << layer.description
              << " (spec. ver. " << apiToString(layer.specVersion)
              << ", impl. ver. " << layer.implementationVersion << ")");
    }
}

void Instance::setEnabledExtensions(const std::vector<std::string> enabledExtensions) {
    this->enabledExtensions = enabledExtensions;
}

void Instance::dumpExtensions() {
    for (const auto& extension : extensionProperties) {
        PRINT(extension.extensionName << " (spec. ver. " << extension.specVersion << ")");
    }
}

std::string Instance::apiToString(int api) {
    int major = (api >> 22) & 0x3FF;
    int minor = (api >> 12) & 0x3FF;
    int patch = api & 0xFFF;
    return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}
