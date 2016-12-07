#include "PipelineLayout.h"

using namespace Vulkan;

PipelineLayout::PipelineLayout(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
}

PipelineLayout::~PipelineLayout() {
    vkDestroyPipelineLayout(device->getHandle(), handle, nullptr);
}

VkResult PipelineLayout::create() {
    return checkError(vkCreatePipelineLayout(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create pipeline layout");
}

void PipelineLayout::setDescriptorSetLayouts(const std::vector<VkDescriptorSetLayout>& setLayouts) {
    assert(setLayouts.size() > 0);
    this->descriptorSetLayouts = setLayouts;
    createInfo.setLayoutCount = setLayouts.size();
    createInfo.pSetLayouts = this->descriptorSetLayouts.data();
}
