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

namespace Vulkan {

std::string resultToString(VkResult result);

template <typename T>
class Handle {
public:
    Handle() = default;

    Handle(T handle) : m_handle(handle) {
        assert(handle != VK_NULL_HANDLE);
    }

    T handle() const { return m_handle; }

    virtual void create() = 0;

protected:
    T m_handle = VK_NULL_HANDLE;
};

}
