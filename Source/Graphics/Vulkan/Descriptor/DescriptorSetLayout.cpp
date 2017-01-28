#include "DescriptorSetLayout.h"

using namespace Vulkan;

DescriptorSetLayout::DescriptorSetLayout(const Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
}

DescriptorSetLayout::~DescriptorSetLayout() {
    destroy();
}

VkResult DescriptorSetLayout::create() {
    createInfo.bindingCount = bindings.size();
    createInfo.pBindings = bindings.data();
    return checkError(vkCreateDescriptorSetLayout(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create descriptor set layout");
}

void DescriptorSetLayout::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyDescriptorSetLayout(device->getHandle(), handle, nullptr))
}

void DescriptorSetLayout::addLayoutBinding(VkDescriptorSetLayoutBinding layoutBinding) {
    bindings.push_back(layoutBinding);
}
