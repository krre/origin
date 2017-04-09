#include "DescriptorSets.h"
#include <assert.h>

using namespace Vulkan;

DescriptorSets::DescriptorSets(const Device* device, const DescriptorPool* descriptorPool) :
    Devicer(device), descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
}

DescriptorSets::~DescriptorSets() {
    destroy();
}

bool DescriptorSets::allocate() {
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
    descriptorWrites.push_back(writeDescriptorSet);
}

void DescriptorSets::writeDescriptors() {
    for (auto& it : descriptorWrites) {
        it.dstSet = collection.at(0); // TODO: Set meaningful value
    }
    vkUpdateDescriptorSets(device->getHandle(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}

void DescriptorSets::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data()));
}
