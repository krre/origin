#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class DescriptorSetLayout : public Handle<VkDescriptorSetLayout> {

public:
    DescriptorSetLayout(const Device* device);
    ~DescriptorSetLayout();
    VkResult create() override;
    void setStageFlags(VkShaderStageFlags flags);

private:
    const Device* device;
    VkDescriptorSetLayoutCreateInfo createInfo = {};
    VkDescriptorSetLayoutBinding bindings = {};
};

} // Vulkan
