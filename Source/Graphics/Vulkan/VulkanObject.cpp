#include "VulkanObject.h"

using namespace Vulkan;

std::map<VkResult, std::string> VulkanObject::resultDescription;

VulkanObject::VulkanObject() {
    if (!resultDescription.size()) {
        resultDescription[VK_SUCCESS] = "Success";
        resultDescription[VK_NOT_READY] = "Not ready";
        resultDescription[VK_TIMEOUT] = "Timeout";
        resultDescription[VK_EVENT_SET] = "Event set";
        resultDescription[VK_EVENT_RESET] = "Event reset";
        resultDescription[VK_INCOMPLETE] = "Incoplete";
        resultDescription[VK_ERROR_OUT_OF_HOST_MEMORY] = "Out of host memory";
        resultDescription[VK_ERROR_OUT_OF_DEVICE_MEMORY] = "Out of device memory";
        resultDescription[VK_ERROR_INITIALIZATION_FAILED] = "Initialization failed";
        resultDescription[VK_ERROR_DEVICE_LOST] = "Device lost";
        resultDescription[VK_ERROR_MEMORY_MAP_FAILED] = "Memory map failed";
        resultDescription[VK_ERROR_LAYER_NOT_PRESENT] = "Layer not present";
        resultDescription[VK_ERROR_EXTENSION_NOT_PRESENT] = "Extension not present";
        resultDescription[VK_ERROR_FEATURE_NOT_PRESENT] = "Feature not present";
        resultDescription[VK_ERROR_INCOMPATIBLE_DRIVER] = "Incompatible driver";
        resultDescription[VK_ERROR_TOO_MANY_OBJECTS] = "Too many objects";
        resultDescription[VK_ERROR_FORMAT_NOT_SUPPORTED] = "Format not supported";
        resultDescription[VK_ERROR_FRAGMENTED_POOL] = "Fragmented pool";
        resultDescription[VK_ERROR_SURFACE_LOST_KHR] = "Surface lost";
        resultDescription[VK_ERROR_NATIVE_WINDOW_IN_USE_KHR] = "Native window in use";
        resultDescription[VK_SUBOPTIMAL_KHR] = "Suboptimal";
        resultDescription[VK_ERROR_OUT_OF_DATE_KHR] = "Out of date";
        resultDescription[VK_ERROR_INCOMPATIBLE_DISPLAY_KHR] = "Incompatible display";
        resultDescription[VK_ERROR_VALIDATION_FAILED_EXT] = "Validation failed";
        resultDescription[VK_ERROR_INVALID_SHADER_NV] = "Invalid shader";
        resultDescription[VK_RESULT_BEGIN_RANGE] = "Invalid shader";
    }
}
