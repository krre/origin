#pragma once
#include "Base/Handle.h"
#include "Device.h"
#include <vector>

namespace Vulkan {

class DescriptorSetLayout : public Handle<VkDescriptorSetLayout> {

public:
    DescriptorSetLayout(const Device* device);
    ~DescriptorSetLayout();
    VkResult create() override;
    void setBindings(const std::vector<VkDescriptorSetLayoutBinding>& bindings);

private:
    const Device* device;
    VkDescriptorSetLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayoutBinding> bindings;
};

} // Vulkan
