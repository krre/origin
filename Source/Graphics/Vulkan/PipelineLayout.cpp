#include "PipelineLayout.h"

using namespace Vulkan;

PipelineLayout::PipelineLayout(const Device* device) : device(device) {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    result = vkCreatePipelineLayout(device->getHandle(), &pipelineLayoutInfo, nullptr, &handle);
}

PipelineLayout::~PipelineLayout() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(device->getHandle(), handle, nullptr);
    }
}
