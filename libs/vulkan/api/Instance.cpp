#include "Instance.h"
#include "DebugReportCallback.h"
#include <iostream>

namespace Vulkan {

Instance::Instance() {
    // Get layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    m_layersProperties.resize(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, m_layersProperties.data());

    // Get extensions
    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    m_extensionProperties.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_extensionProperties.data());

#if defined(_WIN32)
    enabledExtensions = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",
    };
#elif defined(__linux__)
    m_enabledExtensions = {
        "VK_KHR_surface",
        "VK_KHR_xcb_surface",
    };
#endif

    m_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    m_applicationInfo.pApplicationName = "Application";
    m_applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    m_applicationInfo.apiVersion = VK_API_VERSION_1_0;

    m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_createInfo.pApplicationInfo = &m_applicationInfo;
}

Instance::~Instance() {
    m_debugCallback.reset();
    destroy();
}

void Instance::create() {
    std::vector<const char*> layers;
    m_createInfo.enabledLayerCount = m_enabledLayers.size();
    for (const auto& layer : m_enabledLayers) {
        layers.push_back(const_cast<char*>(layer.c_str()));
    }
    m_createInfo.ppEnabledLayerNames = layers.data();

    m_createInfo.enabledExtensionCount = m_enabledExtensions.size();
    std::vector<const char*> extensions;
    for (const auto& extension : m_enabledExtensions) {
        extensions.push_back(const_cast<char*>(extension.c_str()));
    }
    m_createInfo.ppEnabledExtensionNames = extensions.data();

    VULKAN_CHECK_RESULT(vkCreateInstance(&m_createInfo, nullptr, &m_handle), "Failed to create instance");

    if (m_debugReportFlags) {
        for (const auto& layer : m_enabledExtensions) {
            if (layer == "VK_EXT_debug_report") {
                m_debugCallback = std::make_unique<DebugReportCallback>(this);
                m_debugCallback->setFlags(m_debugReportFlags);
                m_debugCallback->create();
                break;
            }
        }
    }
}

void Instance::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyInstance(m_handle, nullptr))
}

void Instance::setEnabledLayers(const std::vector<std::string>& enabledLayers) {
    this->m_enabledLayers = enabledLayers;
}

void Instance::dumpLayers() {
    for (const auto& layer : m_layersProperties) {
        std::cout << layer.layerName << " - " << layer.description
              << " (spec. ver. " << apiToString(layer.specVersion)
              << ", impl. ver. " << layer.implementationVersion << ")" << std::endl;;
    }
}

void Instance::setEnabledExtensions(const std::vector<std::string>& enabledExtensions) {
    this->m_enabledExtensions = enabledExtensions;
}

void Instance::dumpExtensions() {
    for (const auto& extension : m_extensionProperties) {
        std::cout << extension.extensionName << " (spec. ver. " << extension.specVersion << ")" << std::endl;
    }
}

std::string Instance::apiToString(int api) {
    int major = (api >> 22) & 0x3FF;
    int minor = (api >> 12) & 0x3FF;
    int patch = api & 0xFFF;
    return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

}
