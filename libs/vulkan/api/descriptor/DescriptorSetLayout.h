#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorSetLayout : public Handle<VkDescriptorSetLayout>, public Devicer {
public:
    DescriptorSetLayout(Device* device);
    ~DescriptorSetLayout();

    void create() override;

    void addLayoutBinding(VkDescriptorSetLayoutBinding layoutBinding);

private:
    VkDescriptorSetLayoutCreateInfo m_createInfo = {};
    std::vector<VkDescriptorSetLayoutBinding> m_bindings;
};

}
