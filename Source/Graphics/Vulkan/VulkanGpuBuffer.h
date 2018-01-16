#pragma once
#include "Graphics/GpuBuffer.h"
#include <vulkan/vulkan.h>

namespace Origin {

namespace Vulkan {
    class Device;
    class Buffer;
    class DeviceMemory;
}

class VulkanGpuBuffer : public GpuBuffer {

public:
    VulkanGpuBuffer(Usage usage, uint32_t size);
    ~VulkanGpuBuffer();
    VkBuffer getHandle() const;
    void copyToBuffer(Vulkan::Buffer* dstBuffer, VkDeviceSize size);

    void write(const void* data, uint32_t size, uint32_t offset = 0) override;
    void read(void* data, uint32_t size, uint32_t offset = 0) override;

protected:
    uint32_t size = 0;

private:
    Vulkan::Device* device;
    std::unique_ptr<Vulkan::Buffer> buffer;
    std::unique_ptr<Vulkan::DeviceMemory> memory;
    std::unique_ptr<Vulkan::Buffer> stageBuffer; // TODO: Use for staging
};

} // Origin
