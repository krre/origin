#pragma once
#include "Resulter.h"
#include <assert.h>

namespace Vulkan {

template<typename T> class Handle : public Resulter {

public:
    Handle() = default;
    Handle(T handle) : handle(handle) {
        assert(handle != VK_NULL_HANDLE);
    }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    T getHandle() const { return handle; }
    virtual bool create() = 0;

protected:
    T handle = VK_NULL_HANDLE;
};

} // Vulkan
