#include "DescriptorSets.h"
#include <assert.h>

using namespace Vulkan;

DescriptorSets::DescriptorSets(const Device* device, const DescriptorPool* descriptorPool) :
    device(device), descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool = descriptorPool->getHandle();
}

DescriptorSets::~DescriptorSets() {
    vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data());
}

bool DescriptorSets::allocate() {
    allocateInfo.descriptorSetCount = descriptorSetLayouts.size();
    allocateInfo.pSetLayouts = descriptorSetLayouts.data();

    assert(collection.size() == 0 && allocateInfo.descriptorSetCount > 0);
    collection.resize(allocateInfo.descriptorSetCount);
    return checkError(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSets::addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout->getHandle());
}

void DescriptorSets::addDescriptor(Descriptor* descriptor) {
    VkWriteDescriptorSet descriptorWrite = {};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = collection.at(0); // TODO: Set meaningful value
    descriptorWrite.dstBinding = descriptor->getLayoutBinding()->binding;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = descriptor->getLayoutBinding()->descriptorType;
    descriptorWrite.descriptorCount = descriptor->getLayoutBinding()->descriptorCount;
    descriptorWrite.pBufferInfo = descriptor->getBuffer()->getDescriptorInfo();
    descriptorWrites.push_back(descriptorWrite);
}

void DescriptorSets::writeDescriptors() {
    vkUpdateDescriptorSets(device->getHandle(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}
