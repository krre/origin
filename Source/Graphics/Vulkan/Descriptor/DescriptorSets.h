#pragma once
#include "Graphics/Vulkan/Base/Collection.h"
#include "Graphics/Vulkan/Device/Devicer.h"

namespace Vulkan {

class DescriptorPool;

class DescriptorSets : public Collection<VkDescriptorSet>, public Devicer {

public:
    DescriptorSets(const DescriptorPool* descriptorPool, Device* device = nullptr);
    ~DescriptorSets();
    bool allocate();
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    void addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet);
    void addCopyDescriptorSet(VkCopyDescriptorSet copyDescriptorSet);
    void writeDescriptors();
    void destroy() override;

private:
    const DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    std::vector<VkWriteDescriptorSet> writeDescriptorSets;
    std::vector<VkCopyDescriptorSet> copyDescriptorSets;
};

} // Vulkan
