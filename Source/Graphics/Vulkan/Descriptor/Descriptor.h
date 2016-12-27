#pragma once
#include "../../../Core/Object.h"
#include "../MemoryBuffer.h"

namespace Vulkan {

class Descriptor : public Object {

public:
    Descriptor(const Device* device, VkShaderStageFlags stage, VkBufferUsageFlagBits usage, VkDescriptorType descriptorType, uint32_t binding, size_t size, const void* data);
    void update();
    void update(VkDeviceSize offset, VkDeviceSize size);
    Buffer* getBuffer() { return memoryBuffer.getBuffer(); }
    VkDescriptorSetLayoutBinding* getLayoutBinding() { return &layoutBinging; }

private:
    MemoryBuffer memoryBuffer;
    VkDescriptorSetLayoutBinding layoutBinging = {};
};

} // Vulkan
