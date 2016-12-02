#include "Framebuffer.h"

using namespace Vulkan;

Framebuffer::Framebuffer(const Device* device, const RenderPass* renderPass, ImageView* imageView, VkExtent2D extent) :
    device(device),
    imageView(imageView) {
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.renderPass = renderPass->getHandle();
    createInfo.attachmentCount = 1;
    createInfo.width = extent.width;
    createInfo.height = extent.height;
    createInfo.layers = 1;
}

Framebuffer::~Framebuffer() {
    vkDestroyFramebuffer(device->getHandle(), handle, nullptr);
}

void Framebuffer::create() {
    VkImageView attachments[] = {
        imageView->getHandle()
    };

    createInfo.pAttachments = attachments;

    checkError(vkCreateFramebuffer(device->getHandle(), &createInfo, nullptr, &handle));
}
