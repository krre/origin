#include "ComputePipeline.h"

using namespace Vulkan;

ComputePipeline::ComputePipeline(const Device* device) : Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
}

VkResult ComputePipeline::create() {
    VkPipelineCache pc = pipelineCache != nullptr ? pipelineCache->getHandle() : VK_NULL_HANDLE;
    return checkError(vkCreateComputePipelines(device->getHandle(), pc, 1, &createInfo, nullptr, &handle), "Failed to create compute pipelines");
}
