#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Descriptor/DescriptorSetLayout.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout>, public Devicer {

public:
    PipelineLayout(const Device* device);
    ~PipelineLayout();
    VkResult create() override;
    void destroy() override;
    void addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout);

    VkPipelineLayoutCreateInfo createInfo = {};

private:
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
