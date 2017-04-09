#include "Framebuffer.h"

using namespace Vulkan;

Framebuffer::Framebuffer(const Device* device) :
    Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.layers = 1;
}

Framebuffer::~Framebuffer() {
    destroy();
}

void Framebuffer::create() {
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();

    VULKAN_CHECK_RESULT(vkCreateFramebuffer(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create framebuffer");
}

void Framebuffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFramebuffer(device->getHandle(), handle, nullptr))
}

void Framebuffer::addAttachment(VkImageView attachment) {
    attachments.push_back(attachment);
}

void Framebuffer::setWidth(uint32_t width) {
    createInfo.width = width;
}

void Framebuffer::setHeight(uint32_t height) {
    createInfo.height = height;
}

void Framebuffer::setRenderPass(VkRenderPass renderPass) {
    createInfo.renderPass = renderPass;
}
