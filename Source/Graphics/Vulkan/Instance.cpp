#include "Instance.h"

using namespace Vulkan;

Instance::Instance() {
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    extensions.resize(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    std::vector<const char*> extNames;
    for (const auto& extension : extensions) {
        print(extension.extensionName);
        extNames.push_back(extension.extensionName);
    }

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Gagarin";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.pEngineName = "Gagarin Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extNames.data();

    // Using direct assign 'result = vkCreateInstance' causes crash on Windows
    VkResult hackResult = vkCreateInstance(&createInfo, nullptr, &handle);
    result = hackResult;
}

Instance::~Instance() {
    if (handle) {
        vkDestroyInstance(handle, nullptr);
    }
}
