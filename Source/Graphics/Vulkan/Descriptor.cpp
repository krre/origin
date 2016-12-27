#include "Descriptor.h"

using namespace Vulkan;

Descriptor::Descriptor(const Device* device, VkShaderStageFlags stage, VkBufferUsageFlagBits usage, VkDescriptorType descriptorType, uint32_t binding, size_t size, const void* data) :
    memoryBuffer(device, usage, size, data) {

    layoutBinging.binding = binding;
    layoutBinging.descriptorCount = 1;
    layoutBinging.descriptorType = descriptorType;
    layoutBinging.stageFlags = stage;
}

void Descriptor::update() {
    memoryBuffer.update();
}

void Descriptor::update(VkDeviceSize offset, VkDeviceSize size) {
    memoryBuffer.update(offset, size);
}
