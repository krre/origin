#pragma once
#include "Device.h"

namespace Vulkan {

class MemoryBuffer {

public:
    MemoryBuffer(const Device* device);
    ~MemoryBuffer();

private:
    const Device* device;
};

} // Vulkan
