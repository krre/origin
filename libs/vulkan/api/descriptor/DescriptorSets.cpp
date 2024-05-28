#include "DescriptorSets.h"
#include "DescriptorPool.h"
#include <assert.h>

namespace Vulkan {

DescriptorSets::DescriptorSets(Device* device, DescriptorPool* descriptorPool) :
        Devicer(device),
        descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
}

DescriptorSets::~DescriptorSets() {
    destroy();
}

void DescriptorSets::allocate() {
    assert(allocateInfo.descriptorSetCount > 0);
    allocateInfo.descriptorPool = descriptorPool->getHandle();
    allocateInfo.pSetLayouts = descriptorSetLayouts.data();
    VULKAN_CHECK_RESULT(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSets::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout);
    allocateInfo.descriptorSetCount = descriptorSetLayouts.size();
    collection.resize(allocateInfo.descriptorSetCount);
}

void DescriptorSets::addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet) {
    writeDescriptorSets.push_back(writeDescriptorSet);
}

void DescriptorSets::clearWriteDescriptorSets() {
    writeDescriptorSets.clear();
}

void DescriptorSets::addCopyDescriptorSet(VkCopyDescriptorSet copyDescriptorSet) {
    copyDescriptorSets.push_back(copyDescriptorSet);
}

void DescriptorSets::clearCopyDescriptorSets() {
    copyDescriptorSets.clear();
}

void DescriptorSets::updateDescriptorSets() {
    vkUpdateDescriptorSets(device->getHandle(), writeDescriptorSets.size(), writeDescriptorSets.data(), copyDescriptorSets.size(), copyDescriptorSets.data());
}

void DescriptorSets::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data()));
}

} // Vulkan
