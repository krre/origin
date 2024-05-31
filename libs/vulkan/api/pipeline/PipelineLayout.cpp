#include "PipelineLayout.h"

namespace Vulkan {

PipelineLayout::PipelineLayout(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
}

PipelineLayout::~PipelineLayout() {
    destroy();
}

void PipelineLayout::create() {
    createInfo.setLayoutCount = descriptorSetLayouts.size();
    createInfo.pSetLayouts = descriptorSetLayouts.data();
    createInfo.pushConstantRangeCount = pushConstantRanges.size();
    createInfo.pPushConstantRanges = pushConstantRanges.data();
    VULKAN_CHECK_RESULT(vkCreatePipelineLayout(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create pipeline layout");
}

void PipelineLayout::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyPipelineLayout(device->getHandle(), handle, nullptr))
}

void PipelineLayout::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout);
}

void PipelineLayout::addPushConstantRange(VkPushConstantRange pushConstantRange) {
    pushConstantRanges.push_back(pushConstantRange);
}

}
