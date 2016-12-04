#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout> {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    bool create() override;

private:
    const Device* device;
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
};

} // Vulkan
