#pragma once
#include "../Base/Handle.h"
#include "Device.h"

namespace Vulkan {

template<typename T> class Devicer : public Handle<T> {

public:
    Devicer(const Device* device) : device(device) {}
    Devicer(T handle) = delete;
    Devicer() = delete;

    const Device* getDevice() const { return device; }

protected:
    const Device* device = nullptr;
};

} // Vulkan
