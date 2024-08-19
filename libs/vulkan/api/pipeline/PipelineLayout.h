#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout>, public Devicer {
public:
    PipelineLayout(Device* device);
    ~PipelineLayout();

    void create() override;

    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    void addPushConstantRange(VkPushConstantRange pushConstantRange);

private:
    VkPipelineLayoutCreateInfo m_createInfo = {};
    std::vector<VkDescriptorSetLayout> m_descriptorSetLayouts;
    std::vector<VkPushConstantRange> m_pushConstantRanges;
};

}
