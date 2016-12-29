#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "DescriptorPool.h"
#include "Descriptor.h"
#include "DescriptorSetLayout.h"

namespace Vulkan {

class DescriptorSets : public Collection<VkDescriptorSet> {

public:
    DescriptorSets(const Device* device, const DescriptorPool* descriptorPool);
    ~DescriptorSets();
    bool allocate();
    void addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout);
    void addDescriptor(Descriptor* descriptor);
    void writeDescriptors();

private:
    const Device* device;
    const DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    std::vector<VkWriteDescriptorSet> descriptorWrites;
};

} // Vulkan