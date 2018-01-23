#include "ComputePipeline.h"

namespace Vulkan {

ComputePipeline::ComputePipeline(Device* device) :
        Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
}

void ComputePipeline::create() {
    VULKAN_CHECK_RESULT(vkCreateComputePipelines(device->getHandle(), pipelineCache, 1, &createInfo, nullptr, &handle), "Failed to create compute pipelines");
}

} // Vulkan
