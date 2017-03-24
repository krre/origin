#pragma once
#include "Pipeline.h"

namespace Vulkan {

class ComputePipeline : public Pipeline {

public:
    ComputePipeline(const Device* device);
    ~ComputePipeline();
    void create() override;

    VkComputePipelineCreateInfo createInfo = {};
};

} // Vulkan
