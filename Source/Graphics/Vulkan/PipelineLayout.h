#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class PipelineLayout : public VkCreatableObject<VkPipelineLayout> {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    void create() override;

private:
    const Device* device;
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
};

} // Vulkan
