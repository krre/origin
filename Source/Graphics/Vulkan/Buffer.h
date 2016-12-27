#pragma once
#include "Base/Handle.h"
#include "Device.h"
#include "DeviceMemory.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer> {

public:
    Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size, const void* data = nullptr);
    ~Buffer();
    VkResult create() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    void update();
    void update(VkDeviceSize offset, VkDeviceSize size);
    VkDescriptorBufferInfo* getDescriptorInfo() { return &descriptorInfo; }

private:
    const Device* device;
    DeviceMemory memory;
    const void* data;
    VkBufferCreateInfo createInfo = {};
    VkDescriptorBufferInfo descriptorInfo = {};
};

} // Vulkan
