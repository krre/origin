#include "Descriptor.h"

using namespace Vulkan;

Descriptor::Descriptor(const Device* device, VkShaderStageFlags stage, VkBufferUsageFlagBits usage, VkDescriptorType descriptorType, uint32_t binding, size_t size) :
    buffer(device, usage, size) {

    layoutBinging.binding = binding;
    layoutBinging.descriptorCount = 1;
    layoutBinging.descriptorType = descriptorType;
    layoutBinging.stageFlags = stage;

    buffer.create();
}

void Descriptor::update(VkDeviceSize offset, VkDeviceSize size, const void* data) {
    buffer.update(offset, size, data);
}
