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
    createInfo.poolSizeCount = poolSizes.size();
    createInfo.pPoolSizes = poolSizes.data();
    return checkError(vkCreateDescriptorPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create descriptor pool");
}

void DescriptorPool::setPoolSizes(const std::vector<VkDescriptorPoolSize>& poolSizes) {
    this->poolSizes = poolSizes;
}
