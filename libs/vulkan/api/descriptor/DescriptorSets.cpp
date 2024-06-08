#include "DescriptorSets.h"
#include "DescriptorPool.h"
#include <assert.h>

namespace Vulkan {

DescriptorSets::DescriptorSets(Device* device, DescriptorPool* descriptorPool) :
        Devicer(device),
        m_descriptorPool(descriptorPool) {
    m_allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
}

DescriptorSets::~DescriptorSets() {
    destroy();
}

void DescriptorSets::allocate() {
    assert(m_allocateInfo.descriptorSetCount > 0);
    m_allocateInfo.descriptorPool = m_descriptorPool->handle();
    m_allocateInfo.pSetLayouts = m_descriptorSetLayouts.data();
    VULKAN_CHECK_RESULT(vkAllocateDescriptorSets(m_device->handle(), &m_allocateInfo, m_collection.data()), "Failed to allocate descriptor sets");
}

void DescriptorSets::addDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
    m_descriptorSetLayouts.push_back(descriptorSetLayout);
    m_allocateInfo.descriptorSetCount = m_descriptorSetLayouts.size();
    m_collection.resize(m_allocateInfo.descriptorSetCount);
}

void DescriptorSets::addWriteDescriptorSet(VkWriteDescriptorSet writeDescriptorSet) {
    m_writeDescriptorSets.push_back(writeDescriptorSet);
}

void DescriptorSets::clearWriteDescriptorSets() {
    m_writeDescriptorSets.clear();
}

void DescriptorSets::addCopyDescriptorSet(VkCopyDescriptorSet copyDescriptorSet) {
    m_copyDescriptorSets.push_back(copyDescriptorSet);
}

void DescriptorSets::clearCopyDescriptorSets() {
    m_copyDescriptorSets.clear();
}

void DescriptorSets::updateDescriptorSets() {
    vkUpdateDescriptorSets(m_device->handle(), m_writeDescriptorSets.size(), m_writeDescriptorSets.data(), m_copyDescriptorSets.size(), m_copyDescriptorSets.data());
}

void DescriptorSets::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeDescriptorSets(m_device->handle(), m_descriptorPool->handle(), m_collection.size(), m_collection.data()));
}

}
