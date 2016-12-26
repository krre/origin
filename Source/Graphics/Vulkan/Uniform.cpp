#include "Uniform.h"

using namespace Vulkan;

Uniform::Uniform(const Device* device, VkShaderStageFlags stage, uint32_t binding, size_t size, const void* data) :
    memoryBuffer(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, size, data) {

    layoutBinging.binding = binding;
    layoutBinging.descriptorCount = 1;
    layoutBinging.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    layoutBinging.stageFlags = stage;
}

void Uniform::update() {
    memoryBuffer.update();
}
