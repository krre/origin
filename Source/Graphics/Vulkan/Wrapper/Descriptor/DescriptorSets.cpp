#include "DescriptorSets.h"
#include "DescriptorPool.h"
#include <assert.h>

using namespace Vulkan;

DescriptorSets::DescriptorSets(Device* device, DescriptorPool* descriptorPool) :
        Devicer(device),
        descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
}

DescriptorSets::~DescriptorSets() {
    destroy();
}

void DescriptorSets::allocate() {
    allocateInfo.descriptorPool = descriptorPool->getHandle();
    allocateInfo.descriptorSetCount = descriptorSetLayouts.size();
    allocateInfo.pSetLayouts = descriptorSetLayouts.data();

    assert(collection.size() == 0 && allocateInfo.descriptorSetCount > 0);
    collection.resize(allocateInfo.descriptorSetCount);
    VULKAN_CHECK_RESULT(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSets::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout);
}

void DescriptorSets::addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet) {
    writeDescriptorSets.push_back(writeDescriptorSet);
}

void DescriptorSets::addCopyDescriptorSet(VkCopyDescriptorSet copyDescriptorSet) {
    copyDescriptorSets.push_back(copyDescriptorSet);
}

void DescriptorSets::updateDescriptorSets() {
    for (auto& it : writeDescriptorSets) {
        it.dstSet = collection.at(0); // TODO: Set meaningful value
    }
    vkUpdateDescriptorSets(device->getHandle(), writeDescriptorSets.size(), writeDescriptorSets.data(), copyDescriptorSets.size(), copyDescriptorSets.data());
}

void DescriptorSets::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data()));
}
