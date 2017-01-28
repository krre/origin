#pragma once
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorSetLayout : public Devicer<VkDescriptorSetLayout> {

public:
    DescriptorSetLayout(const Device* device);
    ~DescriptorSetLayout();
    VkResult create() override;
    void destroy() override;
    void addLayoutBinding(VkDescriptorSetLayoutBinding layoutBinding);

private:
    VkDescriptorSetLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayoutBinding> bindings;
};

} // Vulkan
