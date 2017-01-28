#pragma once
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Devicer<VkDescriptorPool> {

public:
    DescriptorPool(const Device* device);
    ~DescriptorPool();
    void addPoolSize(VkDescriptorType type, uint32_t count);
    VkResult create() override;
    void destroy() override;
    void setMaxSets(uint32_t maxSets);

private:
    VkDescriptorPoolCreateInfo createInfo = {};
    std::vector<VkDescriptorPoolSize> poolSizes;
    uint32_t maxSets = 0;
};

} // Vulkan
