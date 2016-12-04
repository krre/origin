#pragma once
#include "Base/Object.h"

namespace Vulkan {

template<typename T> class CreatableObject : public Object {

public:
    CreatableObject() {}
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    T getHandle() const { return handle; }
    virtual bool create() = 0;

protected:
    T handle = VK_NULL_HANDLE;
};

} // Vulkan
