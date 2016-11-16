#include "Instance.h"

using namespace Vulkan;

Instance::Instance() {
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
    createInfo.enabledExtensionCount = 0;

    // Using direct assign 'result = vkCreateInstance' causes crash on Windows
    VkResult hackResult = vkCreateInstance(&createInfo, nullptr, &handle);
    result = hackResult;
}

Instance::~Instance() {
    if (handle) {
        vkDestroyInstance(handle, nullptr);
    }
}
