#include "ComputePipeline.h"

using namespace Vulkan;

ComputePipeline::ComputePipeline(const Device* device) : Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
}

VkResult ComputePipeline::create() {
    return checkError(vkCreateComputePipelines(device->getHandle(), VK_NULL_HANDLE, 1, &createInfo, nullptr, &handle), "Failed to create compute pipelines");
}
