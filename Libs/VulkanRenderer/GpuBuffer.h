#pragma once
#include <vulkan/vulkan.h>
#include <memory>

namespace Vulkan {

class Device;
class Buffer;
class DeviceMemory;

class GpuBuffer {

public:
    GpuBuffer(VkBufferUsageFlagBits usage, uint32_t size);
    ~GpuBuffer();
    VkBufferUsageFlagBits getUsage() const { return usage; }
    uint32_t getSize() const { return size; }
    VkBuffer getHandle() const;
    void copyToBuffer(Buffer* dstBuffer, VkDeviceSize size);

    virtual void write(const void* data, uint32_t size, uint32_t offset = 0);
    virtual void read(void* data, uint32_t size, uint32_t offset = 0);

private:
    Device* device;
    std::unique_ptr<Buffer> buffer;
    std::unique_ptr<DeviceMemory> memory;
    std::unique_ptr<Buffer> stageBuffer; // TODO: Use for staging
    uint32_t size = 0;
    VkBufferUsageFlagBits usage;
};

} // Vulkan
