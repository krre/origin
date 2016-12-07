#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "../DescriptorPool.h"

namespace Vulkan {

class DescriptorSetCollection : public Collection<VkDescriptorSet> {

public:
    DescriptorSetCollection(const Device* device, const DescriptorPool* descriptorPool);
    ~DescriptorSetCollection();
    bool allocate(uint32_t count);

private:
    const Device* device;
    const DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
};

} // Vulkan
