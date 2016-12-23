#pragma once
#include "Device.h"
#include "Buffer.h"
#include "DeviceMemory.h"

namespace Vulkan {

class MemoryBuffer {

public:
    MemoryBuffer(const Device* device, VkBufferUsageFlagBits usage);
    ~MemoryBuffer();
    void setData(size_t size, const void* data);
    Buffer* getBuffer() { return &buffer; }

private:
    const Device* device;
    Buffer buffer;
    DeviceMemory memory;
};

} // Vulkan
