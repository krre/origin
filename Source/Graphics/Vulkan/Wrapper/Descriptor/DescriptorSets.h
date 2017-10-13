#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Collection.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class DescriptorPool;

class DescriptorSets : public Collection<VkDescriptorSet>, public Devicer {

public:
    DescriptorSets(Device* device, DescriptorPool* descriptorPool);
    ~DescriptorSets();
    void allocate();
    void addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
    void addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet);
    void addCopyDescriptorSet(VkCopyDescriptorSet copyDescriptorSet);
    void updateDescriptorSets();
    void destroy() override;

private:
    DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
    std::vector<VkWriteDescriptorSet> writeDescriptorSets;
    std::vector<VkCopyDescriptorSet> copyDescriptorSets;
};

} // Vulkan
