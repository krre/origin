#include "PipelineLayout.h"

namespace Vulkan {

PipelineLayout::PipelineLayout(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
}

PipelineLayout::~PipelineLayout() {
    vkDestroyPipelineLayout(m_device->handle(), m_handle, nullptr);
}

void PipelineLayout::create() {
    m_createInfo.setLayoutCount = m_descriptorSetLayouts.size();
    m_createInfo.pSetLayouts = m_descriptorSetLayouts.data();
    m_createInfo.pushConstantRangeCount = m_pushConstantRanges.size();
    m_createInfo.pPushConstantRanges = m_pushConstantRanges.data();
    VULKAN_CHECK_RESULT(vkCreatePipelineLayout(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create pipeline layout");
}

void PipelineLayout::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
    m_descriptorSetLayouts.push_back(descriptorSetLayout);
}

void PipelineLayout::addPushConstantRange(VkPushConstantRange pushConstantRange) {
    m_pushConstantRanges.push_back(pushConstantRange);
}

}
