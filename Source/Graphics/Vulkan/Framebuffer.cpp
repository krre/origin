#include "Framebuffer.h"

using namespace Vulkan;

Framebuffer::Framebuffer(const Device* device, const RenderPass* renderPass, ImageView* imageView, VkExtent2D extent) : device(device) {
    VkImageView attachments[] = {
        imageView->getHandle()
    };

    VkFramebufferCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.renderPass = renderPass->getHandle();
    createInfo.attachmentCount = 1;
    createInfo.pAttachments = attachments;
    createInfo.width = extent.width;
    createInfo.height = extent.height;
    createInfo.layers = 1;
    result = vkCreateFramebuffer(device->getHandle(), &createInfo, nullptr, &handle);
}

Framebuffer::~Framebuffer() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyFramebuffer(device->getHandle(), handle, nullptr);
    }
}
