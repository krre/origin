#pragma once
#include "Device.h"
#include "Buffer.h"
#include "DeviceMemory.h"

namespace Vulkan {

class MemoryBuffer {

public:
    MemoryBuffer(const Device* device, VkBufferUsageFlagBits usage);
    ~MemoryBuffer();

private:
    const Device* device;
    Buffer buffer;
    DeviceMemory memory;
};

} // Vulkan
