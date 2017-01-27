#pragma once
#include "../Base/Handle.h"
#include "../Device/Device.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool> {

public:
    DescriptorPool(const Device* device);
    ~DescriptorPool();
    void addPoolSize(VkDescriptorType type, uint32_t count);
    VkResult create() override;
    void setMaxSets(uint32_t maxSets);

private:
    const Device* device;
    VkDescriptorPoolCreateInfo createInfo = {};
    std::vector<VkDescriptorPoolSize> poolSizes;
    uint32_t maxSets = 0;
};

} // Vulkan
