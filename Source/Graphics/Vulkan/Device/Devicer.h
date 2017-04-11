#pragma once
#include "Device.h"

namespace Vulkan {

class Devicer {

public:
    Devicer(const Device* device);
    Devicer() = delete;

    const Device* getDevice() const { return device; }

protected:
    const Device* device = nullptr;
};

} // Vulkan
