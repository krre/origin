#include "DescriptorSetLayout.h"

using namespace Vulkan;

DescriptorSetLayout::DescriptorSetLayout(const Device* device) : device(device) {
    bindings.binding = 0;
    bindings.descriptorCount = 1;
    bindings.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    createInfo.bindingCount = 1;
    createInfo.pBindings = &bindings;
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
}

DescriptorSetLayout::~DescriptorSetLayout() {
    vkDestroyDescriptorSetLayout(device->getHandle(), handle, nullptr);
}

VkResult DescriptorSetLayout::create() {
    return checkError(vkCreateDescriptorSetLayout(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create descriptor set layout");
}

void DescriptorSetLayout::setStageFlags(VkShaderStageFlags flags) {
    bindings.stageFlags = flags;
}
