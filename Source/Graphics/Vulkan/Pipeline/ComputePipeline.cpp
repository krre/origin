#include "ComputePipeline.h"

using namespace Vulkan;

ComputePipeline::ComputePipeline(const Device* device) :
        Pipeline(device) {
    pipelineBindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
}

void ComputePipeline::create() {
    CHECK_RESULT(vkCreateComputePipelines(device->getHandle(), pipelineCache, 1, &createInfo, nullptr, &handle), "Failed to create compute pipelines");
}
