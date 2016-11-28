#pragma once
#include "VkObject.h"

namespace Vulkan {

template<typename T> class VkCreatableObject : public VkObject {

public:
    VkCreatableObject() {}
    virtual ~VkCreatableObject() {
        if (handle != VK_NULL_HANDLE) {
            destroy();
        }
    }

    bool isValid() const { return handle != VK_NULL_HANDLE; }
    T getHandle() const { return handle; }
    virtual bool create() = 0;
    virtual void destroy() = 0;

protected:
    T handle = VK_NULL_HANDLE;
};

} // Vulkan
