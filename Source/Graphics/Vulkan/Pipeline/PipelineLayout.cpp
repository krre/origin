#include "PipelineLayout.h"

using namespace Vulkan;

PipelineLayout::PipelineLayout(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
}

PipelineLayout::~PipelineLayout() {
    vkDestroyPipelineLayout(device->getHandle(), handle, nullptr);
}

VkResult PipelineLayout::create() {
    createInfo.setLayoutCount = descriptorSetLayouts.size();
    createInfo.pSetLayouts = descriptorSetLayouts.data();
    return checkError(vkCreatePipelineLayout(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create pipeline layout");
}

void PipelineLayout::addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout->getHandle());
}
