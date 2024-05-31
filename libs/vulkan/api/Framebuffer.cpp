#include "Framebuffer.h"
#include "RenderPass.h"
#include "image/ImageView.h"

namespace Vulkan {

Framebuffer::Framebuffer(Device* device) :
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

    VULKAN_CHECK_RESULT(vkCreateFramebuffer(m_device->handle(), &createInfo, nullptr, &m_handle), "Failed to create framebuffer");
}

void Framebuffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFramebuffer(m_device->handle(), m_handle, nullptr))
}

void Framebuffer::addAttachment(ImageView* attachment) {
    attachments.push_back(attachment->handle());
}

void Framebuffer::setWidth(uint32_t width) {
    createInfo.width = width;
}

void Framebuffer::setHeight(uint32_t height) {
    createInfo.height = height;
}

void Framebuffer::setRenderPass(RenderPass* renderPass) {
    createInfo.renderPass = renderPass->handle();
}

}
