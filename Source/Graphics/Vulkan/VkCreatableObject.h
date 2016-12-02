#pragma once
#include "Object.h"

namespace Vulkan {

template<typename T> class VkCreatableObject : public Object {

public:
    VkCreatableObject() {}
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    T getHandle() const { return handle; }
    virtual void create() = 0;

protected:
    T handle = VK_NULL_HANDLE;
};

} // Vulkan
