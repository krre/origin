#pragma once
#include "Base/Handle.h"
#include "Device.h"
#include "DeviceMemory.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer> {

public:
    Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size);
    ~Buffer();
    VkResult create() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    void write(VkDeviceSize offset, VkDeviceSize size, const void* data);
    void read(VkDeviceSize offset, VkDeviceSize size, void* data);
    VkDescriptorBufferInfo* getDescriptorInfo() { return &descriptorInfo; }

private:
    const Device* device;
    DeviceMemory memory;
    VkBufferCreateInfo createInfo = {};
    VkDescriptorBufferInfo descriptorInfo = {};
};

} // Vulkan
