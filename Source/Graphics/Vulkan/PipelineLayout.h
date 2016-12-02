#pragma once
#include "CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class PipelineLayout : public CreatableObject<VkPipelineLayout> {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    bool create() override;

private:
    const Device* device;
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
};

} // Vulkan
