#include "DescriptorPool.h"

using namespace Vulkan;

DescriptorPool::DescriptorPool(const Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
}

DescriptorPool::~DescriptorPool() {
    destroy();
}

void DescriptorPool::addPoolSize(VkDescriptorType type, uint32_t count) {
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = type;
    poolSize.descriptorCount = count;
    poolSizes.push_back(poolSize);
}

VkResult DescriptorPool::create() {
    createInfo.poolSizeCount = poolSizes.size();
    createInfo.pPoolSizes = poolSizes.data();
    if (!createInfo.maxSets) {
        for (auto& poolSize : poolSizes) {
            createInfo.maxSets += poolSize.descriptorCount;
        }
    }
    CHECK_RESULT(vkCreateDescriptorPool(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create descriptor pool");
}

void DescriptorPool::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDescriptorPool(device->getHandle(), handle, nullptr))
}
