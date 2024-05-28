#pragma once
#include "../base/Handle.h"
#include "../device/Devicer.h"
#include <vector>

namespace Vulkan {

class DescriptorPool : public Handle<VkDescriptorPool>, public Devicer {

public:
    DescriptorPool(Device* device);
    ~DescriptorPool();

    void create() override;
    void destroy() override;

    void addPoolSize(VkDescriptorType type, uint32_t count);
    int getPoolSizeCount() const { return poolSizes.size(); }

    void setMaxSets(uint32_t maxSets);
    void reset();

private:
    VkDescriptorPoolCreateInfo createInfo = {};
    std::vector<VkDescriptorPoolSize> poolSizes;
};

} // Vulkan
