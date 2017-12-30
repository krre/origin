#pragma once
#include "Pipeline.h"

namespace Vulkan {

class ComputePipeline : public Pipeline {

public:
    ComputePipeline(Device* device);
    ~ComputePipeline();
    void create() override;
    VkPipelineBindPoint getBindPoint() const override { return VK_PIPELINE_BIND_POINT_COMPUTE; }

private:
    VkComputePipelineCreateInfo createInfo = {};
};

} // Vulkan
