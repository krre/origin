#include "Instance.h"
#include <assert.h>

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

    VkResult result = vkCreateInstance(&createInfo, nullptr, &handle);
    if (result != VK_SUCCESS) {
        switch (result) {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            error = "Out of host memory";
            break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            error = "Out of device memory";
            break;
        case VK_ERROR_INITIALIZATION_FAILED:
            error = "Initialization failed";
            break;
        case VK_ERROR_LAYER_NOT_PRESENT:
            error = "Layer not present";
            break;
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            error = "Extension not present";
            break;
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            error = "Incompatible driver";
        }
    }
}

Instance::~Instance() {
    if (handle) {
        vkDestroyInstance(handle, nullptr);
    }
}
