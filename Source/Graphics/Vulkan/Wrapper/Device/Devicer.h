#pragma once
#include "Device.h"

namespace Origin {

namespace Vulkan {

class Devicer {

public:
    Devicer(Device* device);
    Devicer() = delete;

    Device* getDevice() const { return device; }

protected:
    Device* device;
};

} // Vulkan

} // Origin
