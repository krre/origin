#pragma once
#include "Base/Handle.h"
#include "Device.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool> {

public:
    DescriptorPool(const Device* device);
    ~DescriptorPool();
    VkResult create() override;
    void setPoolSizes(const std::vector<VkDescriptorPoolSize>& poolSizes);
    void setMaxSets(uint32_t maxSets);

private:
    const Device* device;
    VkDescriptorPoolCreateInfo createInfo = {};
    std::vector<VkDescriptorPoolSize> poolSizes;
};

} // Vulkan
