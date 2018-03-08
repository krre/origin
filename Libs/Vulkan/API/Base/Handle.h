#pragma once
#include <assert.h>
#include <stdexcept>
#include <vulkan/vulkan.h>

#define VULKAN_CHECK_RESULT(f, message) \
VkResult result = (f); \
if (result != VK_SUCCESS) { \
    std::string errorMessage = std::string(message) + ": " + Vulkan::resultToString(result) + " in " + __FILE__ + " at line " + std::to_string(__LINE__); \
    throw std::runtime_error(errorMessage); \
}


#define VULKAN_DESTROY_HANDLE(f) \
if (handle != VK_NULL_HANDLE) { \
    (f); \
    handle = VK_NULL_HANDLE; \
}

namespace Vulkan {

std::string resultToString(VkResult result);

template<typename T> class Handle {

public:
    Handle() = default;
    Handle(T handle) : handle(handle) {
        assert(handle != VK_NULL_HANDLE);
        owner = false;
    }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    bool isOwner() const { return owner; }
    T getHandle() const { return handle; }
    virtual void create() = 0;
    virtual void destroy() = 0;

protected:
    T handle = VK_NULL_HANDLE;
    bool owner = true;
};

} // Vulkan

