#include "DescriptorPool.h"

namespace Vulkan {

DescriptorPool::DescriptorPool(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    createInfo.maxSets = 1;
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

void DescriptorPool::setMaxSets(uint32_t maxSets) {
    createInfo.maxSets = maxSets;
}

void DescriptorPool::create() {
    assert(poolSizes.size() != 0);
    createInfo.poolSizeCount = poolSizes.size();
    createInfo.pPoolSizes = poolSizes.data();
    VULKAN_CHECK_RESULT(vkCreateDescriptorPool(m_device->handle(), &createInfo, nullptr, &m_handle), "Failed to create descriptor pool");
}

void DescriptorPool::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDescriptorPool(m_device->handle(), m_handle, nullptr))
}

void DescriptorPool::reset() {
    vkResetDescriptorPool(m_device->handle(), m_handle, 0);
}

}
