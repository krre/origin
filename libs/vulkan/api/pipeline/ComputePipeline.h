#pragma once
#include "Pipeline.h"

namespace Vulkan {

class ComputePipeline : public Pipeline {

public:
    ComputePipeline(Device* device);
    void create() override;
    void setPipelineLayout(VkPipelineLayout layout);
    VkPipelineBindPoint getBindPoint() const override { return VK_PIPELINE_BIND_POINT_COMPUTE; }

private:
    VkComputePipelineCreateInfo createInfo = {};
};

} // Vulkan
