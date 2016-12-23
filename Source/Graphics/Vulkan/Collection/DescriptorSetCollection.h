#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "../DescriptorPool.h"
#include "../Buffer.h"

namespace Vulkan {

class DescriptorSetCollection : public Collection<VkDescriptorSet> {

public:
    DescriptorSetCollection(const Device* device, const DescriptorPool* descriptorPool);
    ~DescriptorSetCollection();
    bool allocate();
    void setDescriptorSetLayouts(const std::vector<VkDescriptorSetLayout>& setLayouts);
    void update(const Buffer* buffer);

private:
    const Device* device;
    const DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
