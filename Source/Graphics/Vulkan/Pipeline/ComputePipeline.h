#pragma once
#include "Pipeline.h"

namespace Vulkan {

class ComputePipeline : public Pipeline {

public:
    ComputePipeline(const Device* device);
    ~ComputePipeline();
    VkResult create() override;

    VkComputePipelineCreateInfo createInfo = {};
};

} // Vulkan
