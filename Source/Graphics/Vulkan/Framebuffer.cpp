#include "Framebuffer.h"

using namespace Vulkan;

Framebuffer::Framebuffer(const Device* device, const RenderPass* renderPass, VkExtent2D extent) :
    Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.renderPass = renderPass->getHandle();

    createInfo.width = extent.width;
    createInfo.height = extent.height;
    createInfo.layers = 1;
}

Framebuffer::~Framebuffer() {
    destroy();
}

VkResult Framebuffer::create() {
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();

    return checkError(vkCreateFramebuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create framebuffer");
}

void Framebuffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFramebuffer(device->getHandle(), handle, nullptr))
}

void Framebuffer::addAttachment(VkImageView attachment) {
    attachments.push_back(attachment);
}
