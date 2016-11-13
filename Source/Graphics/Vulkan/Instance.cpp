#include "Instance.h"
#include <assert.h>

using namespace Vulkan;

Instance::Instance() {
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Gagarin";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.pEngineName = "Gagarin Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.enabledExtensionCount = 0;
}

Instance::~Instance() {
    if (handle) {
        vkDestroyInstance(handle, NULL);
    }
}

bool Instance::create() {
    assert(!handle && "Vulkan instance already is created");

    VkResult result = vkCreateInstance(&createInfo, NULL, &handle);
    if (result == VK_SUCCESS) {
        return true;
    } else {
        switch (result) {
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            error = "Out of host memory";
            return false;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            error = "Out of device memory";
            return false;
        case VK_ERROR_INITIALIZATION_FAILED:
            error = "Initialization failed";
            return false;
        case VK_ERROR_LAYER_NOT_PRESENT:
            error = "Layer not present";
            return false;
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            error = "Extension not present";
            return false;
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            error = "Incompatible driver";
            return false;
        }
    }

    return false;
}
