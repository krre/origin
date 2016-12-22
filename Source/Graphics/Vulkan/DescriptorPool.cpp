#include "DescriptorPool.h"

using namespace Vulkan;

DescriptorPool::DescriptorPool(const Device* device) : device(device) {
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = 1;

    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    createInfo.poolSizeCount = 1;
    createInfo.pPoolSizes = &poolSize;
    createInfo.maxSets = 1;
}

DescriptorPool::~DescriptorPool() {
    vkDestroyDescriptorPool(device->getHandle(), handle, nullptr);
}

VkResult DescriptorPool::create() {
    return checkError(vkCreateDescriptorPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create descriptor pool");
}
