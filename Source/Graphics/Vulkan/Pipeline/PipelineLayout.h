#pragma once
#include "../Base/Handle.h"
#include "../Device.h"
#include "../Descriptor/DescriptorSetLayout.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout> {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    VkResult create() override;
    void addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout);

private:
    const Device* device;
    VkPipelineLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
