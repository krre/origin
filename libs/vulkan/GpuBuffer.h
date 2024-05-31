#pragma once
#include <vulkan/vulkan.h>
#include <memory>

namespace Vulkan {

class Device;
class Buffer;
class DeviceMemory;

class GpuBuffer {

public:
    GpuBuffer(Device* device, VkBufferUsageFlagBits usage, uint32_t size);
    ~GpuBuffer();

    VkBufferUsageFlagBits usage() const { return m_usage; }
    uint32_t size() const { return m_size; }
    VkBuffer handle() const;
    void copyToBuffer(Buffer* dstBuffer, VkDeviceSize size);

    void write(const void* data, uint32_t size, uint32_t offset = 0);
    void read(void* data, uint32_t size, uint32_t offset = 0);

private:
    std::unique_ptr<Buffer> buffer;
    std::unique_ptr<DeviceMemory> memory;
    std::unique_ptr<Buffer> stageBuffer; // TODO: Use for staging
    uint32_t m_size = 0;
    VkBufferUsageFlagBits m_usage;
};

}
