#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"

namespace Vulkan {

class DeviceMemory;
class CommandPool;

class Buffer : public Handle<VkBuffer>, public Devicer {

public:

    Buffer(Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size, bool moveToDevice = true);
    ~Buffer();
    void create() override;
    void destroy() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    void write(const void* data, VkDeviceSize size, VkDeviceSize offset = 0);
    void read(void* data, VkDeviceSize size, VkDeviceSize offset = 0);
    void copyToBuffer(CommandPool* commandPool, Buffer* dstBuffer, VkDeviceSize size);
    const VkDescriptorBufferInfo* getDescriptorInfo() const { return &descriptorInfo; }

private:
    VkBufferCreateInfo createInfo = {};
    VkDescriptorBufferInfo descriptorInfo = {};
    std::unique_ptr<DeviceMemory> memory;
    bool moveToDevice;
};

} // Vulkan
