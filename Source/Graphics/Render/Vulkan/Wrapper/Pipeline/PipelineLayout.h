#pragma once
#include "Graphics/Render/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Render/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout>, public Devicer {

public:
    PipelineLayout(Device* device = nullptr);
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
