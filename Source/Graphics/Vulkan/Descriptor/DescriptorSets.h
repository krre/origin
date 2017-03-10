#pragma once
#include "../Base/Collection.h"
#include "../Device/Devicer.h"
#include "DescriptorPool.h"
#include "DescriptorSetLayout.h"

namespace Vulkan {

class DescriptorSets : public Collection<VkDescriptorSet>, public Devicer {

public:
    DescriptorSets(const Device* device, const DescriptorPool* descriptorPool);
    ~DescriptorSets();
    bool allocate();
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    void addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet);
    void writeDescriptors();
    void destroy() override;

    VkDescriptorSetAllocateInfo allocateInfo = {};

private:
    const DescriptorPool* descriptorPool;
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    std::vector<VkWriteDescriptorSet> descriptorWrites;
};

} // Vulkan
