#include "PipelineLayout.h"

using namespace Vulkan;

PipelineLayout::PipelineLayout(const Device* device) : device(device) {
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
}

PipelineLayout::~PipelineLayout() {
    vkDestroyPipelineLayout(device->getHandle(), handle, nullptr);
}

void PipelineLayout::create() {
    checkError(vkCreatePipelineLayout(device->getHandle(), &pipelineLayoutInfo, nullptr, &handle));
}
