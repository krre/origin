#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorSetLayout : public Handle<VkDescriptorSetLayout>, public Devicer {

public:
    DescriptorSetLayout(Device* device);
    ~DescriptorSetLayout();
    void create() override;
    void destroy() override;
    void addLayoutBinding(VkDescriptorSetLayoutBinding layoutBinding);

private:
    VkDescriptorSetLayoutCreateInfo createInfo = {};
    std::vector<VkDescriptorSetLayoutBinding> bindings;
};

} // Vulkan
