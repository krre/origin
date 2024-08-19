#include "ComputePipeline.h"

namespace Vulkan {

ComputePipeline::ComputePipeline(Device* device) :
        Pipeline(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
}

void ComputePipeline::create() {
    assert(m_shaderStages.size() == 1);
    m_createInfo.stage = m_shaderStages.at(0);
    VULKAN_CHECK_RESULT(vkCreateComputePipelines(m_device->handle(), m_pipelineCache, 1, &m_createInfo, nullptr, &m_handle), "Failed to create compute pipelines");
}

void ComputePipeline::setPipelineLayout(VkPipelineLayout layout) {
    m_createInfo.layout = layout;
}

}
