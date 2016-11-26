#include "Framebuffer.h"

using namespace Vulkan;

Framebuffer::Framebuffer(const Device* device) : device(device) {
    VkFramebufferCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    result = vkCreateFramebuffer(device->getHandle(), &createInfo, nullptr, &handle);
}

Framebuffer::~Framebuffer() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyFramebuffer(device->getHandle(), handle, nullptr);
    }
}
