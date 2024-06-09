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
if (m_handle != VK_NULL_HANDLE) { \
    (f); \
    m_handle = VK_NULL_HANDLE; \
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
    bool isValid() const { return m_handle != VK_NULL_HANDLE; }
    T handle() const { return m_handle; }
    virtual void create() = 0;
    virtual void destroy() = 0;

protected:
    T m_handle = VK_NULL_HANDLE;
};

}
