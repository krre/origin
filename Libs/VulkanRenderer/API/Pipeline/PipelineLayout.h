#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout>, public Devicer {

public:
    PipelineLayout(Device* device);
    ~PipelineLayout();
    void create() override;
    void destroy() override;
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    void addPushConstantRange(VkPushConstantRange pushConstantRange);

private:
    VkPipelineLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    std::vector<VkPushConstantRange> pushConstantRanges;

};

} // Vulkan

} // Origin
