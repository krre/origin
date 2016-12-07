#include "DescriptorSetCollection.h"
#include <assert.h>

using namespace Vulkan;

DescriptorSetCollection::DescriptorSetCollection(const Device* device, const DescriptorPool* descriptorPool) :
    device(device), descriptorPool(descriptorPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool = descriptorPool->getHandle();
//    allocateInfo.pSetLayouts = layouts;
}

DescriptorSetCollection::~DescriptorSetCollection() {
    vkFreeDescriptorSets(device->getHandle(), descriptorPool->getHandle(), collection.size(), collection.data());
}

bool DescriptorSetCollection::allocate(uint32_t count) {
    assert(collection.size() == 0 && count > 0);
    allocateInfo.descriptorSetCount = count;

    return checkError(vkAllocateDescriptorSets(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate descriptor sets");
}
