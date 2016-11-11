#include "Instance.h"

using namespace Vulkan;

Instance::Instance() {

}

Instance::~Instance() {
    if (pInstance != nullptr) {
        vkDestroyInstance(*pInstance, NULL);
    }
}

bool Instance::create() {
    VkResult result = vkCreateInstance(pCreateInfo, NULL, pInstance);
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
        default:
            return false;
        }
    }
}
