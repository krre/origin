#pragma once
#include "Result.h"
#include "../../../Core/Common.h"
#include <assert.h>

#define VULKAN_DESTROY_HANDLE(f) { \
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
    }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    T getHandle() const { return handle; }
    virtual VkResult create() = 0;
    virtual void destroy() = 0;

protected:
    T handle = VK_NULL_HANDLE;
};

} // Vulkan
