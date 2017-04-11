#pragma once
#include "Pipeline.h"

namespace Vulkan {

class ComputePipeline : public Pipeline {

public:
    ComputePipeline(Device* device = nullptr);
    ~ComputePipeline();
    void create() override;
    VkPipelineBindPoint getBindPoint() const override { return VK_PIPELINE_BIND_POINT_COMPUTE; }

    VkComputePipelineCreateInfo createInfo = {};
};

} // Vulkan
