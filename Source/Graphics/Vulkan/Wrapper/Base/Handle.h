#pragma once
#include "Core/Common.h"
#include <assert.h>
#include <stdexcept>
#include <vulkan/vulkan.h>

static std::string resultToString(VkResult result) {
    switch (result) {
        case VK_SUCCESS: return "Success";
        case VK_NOT_READY: return "Not ready";
        case VK_TIMEOUT: return "Timeout";
        case VK_EVENT_SET: return "Event set";
        case VK_EVENT_RESET: return "Event reset";
        case VK_INCOMPLETE: return "Incoplete";
        case VK_ERROR_OUT_OF_HOST_MEMORY: return "Out of host memory";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "Out of device memory";
        case VK_ERROR_INITIALIZATION_FAILED: return "Initialization failed";
        case VK_ERROR_DEVICE_LOST: return "Device lost";
        case VK_ERROR_MEMORY_MAP_FAILED: return "Memory map failed";
        case VK_ERROR_LAYER_NOT_PRESENT: return "Layer not present";
        case VK_ERROR_EXTENSION_NOT_PRESENT: return "Extension not present";
        case VK_ERROR_FEATURE_NOT_PRESENT: return "Feature not present";
        case VK_ERROR_INCOMPATIBLE_DRIVER: return "Incompatible driver";
        case VK_ERROR_TOO_MANY_OBJECTS: return "Too many objects";
        case VK_ERROR_FORMAT_NOT_SUPPORTED: return "Format not supported";
        case VK_ERROR_FRAGMENTED_POOL: return "Fragmented pool";
        case VK_ERROR_SURFACE_LOST_KHR: return "Surface lost";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "Native window in use";
        case VK_SUBOPTIMAL_KHR: return "Suboptimal";
        case VK_ERROR_OUT_OF_DATE_KHR: return "Out of date";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "Incompatible display";
        case VK_ERROR_VALIDATION_FAILED_EXT: return "Validation failed";
        case VK_ERROR_INVALID_SHADER_NV: return "Invalid shader";
        case VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR: return "Invalid external handle";
        case VK_ERROR_OUT_OF_POOL_MEMORY_KHR: return "Out of pool memory";
        case VK_RESULT_MAX_ENUM:
        case VK_RESULT_RANGE_SIZE:
        return std::string("Unknown result code: ") + std::to_string(result);
    }
}

#define VULKAN_CHECK_RESULT(f, message) { \
    if (!isOwner) return; \
    VkResult result = (f); \
    if (result != VK_SUCCESS) { \
        std::string errorMessage = std::string(message) + ": " + resultToString(result) + " in " + __FILE__ + " at line " + std::to_string(__LINE__); \
        throw std::runtime_error(errorMessage); \
    } \
}

#define VULKAN_DESTROY_HANDLE(f) { \
    if (!isOwner) return; \
    if (handle != VK_NULL_HANDLE) { \
        (f); \
        handle = VK_NULL_HANDLE; \
    } \
} \

namespace Vulkan {

template<typename T> class Handle {

public:
    Handle() = default;
    Handle(T handle) : handle(handle) {
        assert(handle != VK_NULL_HANDLE);
        isOwner = false;
    }
    bool getIsValid() const { return handle != VK_NULL_HANDLE; }
    bool getIsOwner() const { return isOwner; }
    T getHandle() const { return handle; }
    virtual void create() = 0;
    virtual void destroy() = 0;

protected:
    T handle = VK_NULL_HANDLE;
    bool isOwner = true;
};

} // Vulkan
