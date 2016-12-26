#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "../DescriptorPool.h"
#include "../Buffer.h"
#include "../DescriptorSetLayout.h"

namespace Vulkan {

class DescriptorSetCollection : public Collection<VkDescriptorSet> {

public:
    DescriptorSetCollection(const Device* device, const DescriptorPool* descriptorPool);
    ~DescriptorSetCollection();
    bool allocate();
    void addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout);
    void update(const std::vector<Buffer*>& buffers);

private:
    const Device* device;
    const DescriptorPool* descriptorPool;
    VkDescriptorSetAllocateInfo allocateInfo = {};
    std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
};

} // Vulkan
