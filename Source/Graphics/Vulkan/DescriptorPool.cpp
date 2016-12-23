#include "DescriptorPool.h"

using namespace Vulkan;

DescriptorPool::DescriptorPool(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    createInfo.maxSets = 2;
}

DescriptorPool::~DescriptorPool() {
    vkDestroyDescriptorPool(device->getHandle(), handle, nullptr);
}

VkResult DescriptorPool::create() {
    VkDescriptorPoolSize poolSize1 = {};
    poolSize1.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize1.descriptorCount = 1;

    VkDescriptorPoolSize poolSize2 = {};
    poolSize2.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize2.descriptorCount = 1;

    VkDescriptorPoolSize poolSizes[] = { poolSize1, poolSize2 };
    createInfo.poolSizeCount = 2;
    createInfo.pPoolSizes = poolSizes;
    return checkError(vkCreateDescriptorPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create descriptor pool");
}
