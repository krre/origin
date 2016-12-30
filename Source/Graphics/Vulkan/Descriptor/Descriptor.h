#pragma once
#include "../../../Core/Object.h"
#include "../Buffer.h"

namespace Vulkan {

class Descriptor : public Object {

public:
    Descriptor(const Device* device, VkShaderStageFlags stage, VkBufferUsageFlagBits usage, VkDescriptorType descriptorType, uint32_t binding, size_t size);
    void write(VkDeviceSize offset, VkDeviceSize size, const void* data);
    Buffer* getBuffer() { return &buffer; }
    VkDescriptorSetLayoutBinding* getLayoutBinding() { return &layoutBinging; }

private:
    Buffer buffer;
    VkDescriptorSetLayoutBinding layoutBinging = {};
};

} // Vulkan
