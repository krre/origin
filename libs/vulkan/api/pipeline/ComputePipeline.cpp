#include "ComputePipeline.h"

namespace Vulkan {

ComputePipeline::ComputePipeline(Device* device) :
        Pipeline(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
}

void ComputePipeline::create() {
    assert(shaderStages.size() == 1);
    createInfo.stage = shaderStages.at(0);
    VULKAN_CHECK_RESULT(vkCreateComputePipelines(device->getHandle(), pipelineCache, 1, &createInfo, nullptr, &handle), "Failed to create compute pipelines");
}

void ComputePipeline::setPipelineLayout(VkPipelineLayout layout) {
    createInfo.layout = layout;
}

}
