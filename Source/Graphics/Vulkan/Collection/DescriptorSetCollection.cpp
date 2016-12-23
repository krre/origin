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
    assert(collection.size() == 0 && allocateInfo.descriptorSetCount > 0);
    collection.resize(allocateInfo.descriptorSetCount);
    return checkError(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSetCollection::setDescriptorSetLayouts(const std::vector<VkDescriptorSetLayout>& setLayouts) {
    assert(setLayouts.size() > 0);
    this->descriptorSetLayouts = setLayouts;
    allocateInfo.descriptorSetCount = setLayouts.size();
    allocateInfo.pSetLayouts = this->descriptorSetLayouts.data();
}

void DescriptorSetCollection::update(const Buffer* buffer) {
    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = buffer->getHandle();
    bufferInfo.offset = 0;
    bufferInfo.range = buffer->getSize();

    VkWriteDescriptorSet descriptorWrite = {};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = *getData();
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device->getHandle(), 1, &descriptorWrite, 0, nullptr);
}
