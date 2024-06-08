#pragma once
#include "Device.h"

namespace Vulkan {

class Devicer {

public:
    Devicer(Device* device);
    Devicer() = delete;

    Device* device() const { return m_device; }

protected:
    Device* m_device = nullptr;
};

}
