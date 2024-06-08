#include "DescriptorSetLayout.h"

namespace Vulkan {

DescriptorSetLayout::DescriptorSetLayout(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
}

DescriptorSetLayout::~DescriptorSetLayout() {
    destroy();
}

void DescriptorSetLayout::create() {
    m_createInfo.bindingCount = m_bindings.size();
    m_createInfo.pBindings = m_bindings.data();
    VULKAN_CHECK_RESULT(vkCreateDescriptorSetLayout(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create descriptor set layout");
}

void DescriptorSetLayout::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDescriptorSetLayout(m_device->handle(), m_handle, nullptr))
}

void DescriptorSetLayout::addLayoutBinding(VkDescriptorSetLayoutBinding layoutBinding) {
    m_bindings.push_back(layoutBinding);
}

}
