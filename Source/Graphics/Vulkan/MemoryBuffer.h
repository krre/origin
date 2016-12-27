#pragma once
#include "Device.h"
#include "Buffer.h"
#include "DeviceMemory.h"

namespace Vulkan {

class MemoryBuffer {

public:
    MemoryBuffer(const Device* device, VkBufferUsageFlagBits usage, size_t size, const void* data);
    void update();
    void update(VkDeviceSize offset, VkDeviceSize size);
    Buffer* getBuffer() { return &buffer; }

private:
    const Device* device;
    Buffer buffer;
    DeviceMemory memory;
    const void* data;
};

} // Vulkan
