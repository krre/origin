#pragma once
#include "Device.h"

namespace Vulkan {

class Uniform {

public:
    Uniform(const Device* device);
    ~Uniform();

private:
    const Device* device;
};

} // Vulkan
