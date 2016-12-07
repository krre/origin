#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout> {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    VkResult create() override;
    void setDescriptorSetLayouts(const std::vector<VkDescriptorSetLayout>& setLayouts);


private:
    const Device* device;
    VkPipelineLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
