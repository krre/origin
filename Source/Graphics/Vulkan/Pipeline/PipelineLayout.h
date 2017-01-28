#pragma once
#include "../Device/Devicer.h"
#include "../Descriptor/DescriptorSetLayout.h"

namespace Vulkan {

class PipelineLayout : public Devicer<VkPipelineLayout> {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    VkResult create() override;
    void destroy() override;
    void addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout);

private:
    VkPipelineLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
