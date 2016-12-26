#include "DescriptorSetCollection.h"
#include <assert.h>

using namespace Vulkan;

DescriptorSetCollection::DescriptorSetCollection(const Device* device, const DescriptorPool* descriptorPool) :
    device(device), descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool = descriptorPool->getHandle();
}

DescriptorSetCollection::~DescriptorSetCollection() {
    vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data());
}

bool DescriptorSetCollection::allocate() {
    allocateInfo.descriptorSetCount = descriptorSetLayouts.size();
    allocateInfo.pSetLayouts = descriptorSetLayouts.data();

    assert(collection.size() == 0 && allocateInfo.descriptorSetCount > 0);
    collection.resize(allocateInfo.descriptorSetCount);
    return checkError(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSetCollection::addDescriptorSetLayout(const DescriptorSetLayout* descriptorSetLayout) {
    descriptorSetLayouts.push_back(descriptorSetLayout->getHandle());
}

void DescriptorSetCollection::addUniform(Uniform* uniform) {
    VkWriteDescriptorSet descriptorWrite = {};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = collection.at(0); // TODO: Set meaningful value
    descriptorWrite.dstBinding = uniform->getLayoutBinding()->binding;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = uniform->getLayoutBinding()->descriptorType;
    descriptorWrite.descriptorCount = uniform->getLayoutBinding()->descriptorCount;
    descriptorWrite.pBufferInfo = uniform->getBuffer()->getDescriptorInfo();
    descriptorWrites.push_back(descriptorWrite);
}

void DescriptorSetCollection::writeUniforms() {
    vkUpdateDescriptorSets(device->getHandle(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}
