#pragma once
#include "Graphics/Vulkan/Base/Collection.h"
#include "Graphics/Vulkan/Device/Devicer.h"
#include "DescriptorPool.h"
#include "DescriptorSetLayout.h"

namespace Vulkan {

class DescriptorSets : public Collection<VkDescriptorSet>, public Devicer {

public:
    DescriptorSets(const DescriptorPool* descriptorPool, Device* device = nullptr);
    ~DescriptorSets();
    bool allocate();
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    void addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet);
    void writeDescriptors();
    void destroy() override;

private:
    const DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    std::vector<VkWriteDescriptorSet> descriptorWrites;
};

} // Vulkan
