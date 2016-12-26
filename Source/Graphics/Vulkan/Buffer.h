#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class Buffer : public Handle<VkBuffer> {

public:
    Buffer(const Device* device, VkBufferUsageFlagBits usage, VkDeviceSize size);
    ~Buffer();
    VkResult create() override;
    VkDeviceSize getSize() const { return createInfo.size; }
    VkDescriptorBufferInfo* getDescriptorInfo() { return &descriptorInfo; }

private:
    const Device* device;
    VkBufferCreateInfo createInfo = {};
    VkDescriptorBufferInfo descriptorInfo = {};
};

} // Vulkan
