#pragma once
#include "Device.h"
#include "Buffer.h"
#include "DeviceMemory.h"

namespace Vulkan {

class MemoryBuffer {

public:
    MemoryBuffer(const Device* device, VkBufferUsageFlagBits usage);
    ~MemoryBuffer();
    void setSize(VkDeviceSize size);

private:
    const Device* device;
    Buffer buffer;
    DeviceMemory memory;
};

} // Vulkan
