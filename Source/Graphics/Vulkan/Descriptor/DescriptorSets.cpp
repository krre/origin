#include "DescriptorSets.h"
#include <assert.h>

using namespace Vulkan;

DescriptorSets::DescriptorSets(const Device* device, const DescriptorPool* descriptorPool) :
    Devicer(device), descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool = descriptorPool->getHandle();
}

DescriptorSets::~DescriptorSets() {
    destroy();
}

bool DescriptorSets::allocate() {
    allocateInfo.descriptorSetCount = descriptorSetLayouts.size();
    allocateInfo.pSetLayouts = descriptorSetLayouts.data();

    assert(collection.size() == 0 && allocateInfo.descriptorSetCount > 0);
    collection.resize(allocateInfo.descriptorSetCount);
    return checkError(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSets::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout);
}

void DescriptorSets::addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet) {
    descriptorWrites.push_back(writeDescriptorSet);
}

void DescriptorSets::addDescriptor(Descriptor* descriptor) {
    VkWriteDescriptorSet descriptorWrite = {};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = collection.at(0); // TODO: Set meaningful value
    descriptorWrite.dstBinding = descriptor->setLayoutBinding.binding;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = descriptor->setLayoutBinding.descriptorType;
    descriptorWrite.descriptorCount = descriptor->setLayoutBinding.descriptorCount;
    descriptorWrite.pBufferInfo = &descriptor->getBuffer()->descriptorInfo;
    if (descriptor->getImage() != nullptr) {
        descriptorWrite.pImageInfo = &descriptor->getImage()->descriptorInfo;
    }
    descriptorWrites.push_back(descriptorWrite);
}

void DescriptorSets::writeDescriptors() {
    vkUpdateDescriptorSets(device->getHandle(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}

void DescriptorSets::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data()));
}
