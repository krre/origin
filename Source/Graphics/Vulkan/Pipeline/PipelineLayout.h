#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include "../Descriptor/DescriptorSetLayout.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout>, public Devicer {

public:
    PipelineLayout(Device* device = nullptr);
    ~PipelineLayout();
    void create() override;
    void destroy() override;
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);

    VkPipelineLayoutCreateInfo createInfo = {};

private:
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
