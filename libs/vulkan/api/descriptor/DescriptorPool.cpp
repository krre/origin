#include "DescriptorPool.h"

namespace Vulkan {

DescriptorPool::DescriptorPool(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    m_createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    m_createInfo.maxSets = 1;
}

DescriptorPool::~DescriptorPool() {
    vkDestroyDescriptorPool(m_device->handle(), m_handle, nullptr);
}

void DescriptorPool::addPoolSize(VkDescriptorType type, uint32_t count) {
    VkDescriptorPoolSize poolSize = {};
    poolSize.type = type;
    poolSize.descriptorCount = count;
    m_poolSizes.push_back(poolSize);
}

void DescriptorPool::setMaxSets(uint32_t maxSets) {
    m_createInfo.maxSets = maxSets;
}

void DescriptorPool::create() {
    assert(m_poolSizes.size() != 0);
    m_createInfo.poolSizeCount = m_poolSizes.size();
    m_createInfo.pPoolSizes = m_poolSizes.data();
    VULKAN_CHECK_RESULT(vkCreateDescriptorPool(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create descriptor pool");
}

void DescriptorPool::reset() {
    vkResetDescriptorPool(m_device->handle(), m_handle, 0);
}

}
