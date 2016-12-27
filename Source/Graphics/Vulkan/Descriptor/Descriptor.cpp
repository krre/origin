#include "Descriptor.h"

using namespace Vulkan;

Descriptor::Descriptor(const Device* device, VkShaderStageFlags stage, VkBufferUsageFlagBits usage, VkDescriptorType descriptorType, uint32_t binding, size_t size, const void* data) :
    buffer(device, usage, size, data) {

    layoutBinging.binding = binding;
    layoutBinging.descriptorCount = 1;
    layoutBinging.descriptorType = descriptorType;
    layoutBinging.stageFlags = stage;

    buffer.create();
}

void Descriptor::update() {
    buffer.update();
}

void Descriptor::update(VkDeviceSize offset, VkDeviceSize size) {
    buffer.update(offset, size);
}
