#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class DescriptorSetLayout : public Handle<VkDescriptorSetLayout> {

public:
    DescriptorSetLayout(const Device* device);
    ~DescriptorSetLayout();
    VkResult create() override;

private:
    const Device* device;
    VkDescriptorSetLayoutCreateInfo createInfo = {};
};

} // Vulkan
