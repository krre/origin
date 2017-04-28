#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"
#include "Graphics/Vulkan/Descriptor/DescriptorSetLayout.h"

namespace Vulkan {

class PipelineLayout : public Handle<VkPipelineLayout>, public Devicer {

public:
    PipelineLayout(Device* device = nullptr);
    ~PipelineLayout();
    void create() override;
    void destroy() override;
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);

private:
    VkPipelineLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
