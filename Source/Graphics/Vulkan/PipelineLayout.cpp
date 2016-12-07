#include "PipelineLayout.h"

using namespace Vulkan;

PipelineLayout::PipelineLayout(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    createInfo.setLayoutCount = 0;
    createInfo.pushConstantRangeCount = 0;
}

PipelineLayout::~PipelineLayout() {
    vkDestroyPipelineLayout(device->getHandle(), handle, nullptr);
}

VkResult PipelineLayout::create() {
    return checkError(vkCreatePipelineLayout(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create pipeline layout");
}
