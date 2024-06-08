#include "Framebuffer.h"
#include "RenderPass.h"
#include "image/ImageView.h"

namespace Vulkan {

Framebuffer::Framebuffer(Device* device) :
    Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    m_createInfo.layers = 1;
}

Framebuffer::~Framebuffer() {
    destroy();
}

void Framebuffer::create() {
    m_createInfo.attachmentCount = m_attachments.size();
    m_createInfo.pAttachments = m_attachments.data();

    VULKAN_CHECK_RESULT(vkCreateFramebuffer(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create framebuffer");
}

void Framebuffer::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyFramebuffer(m_device->handle(), m_handle, nullptr))
}

void Framebuffer::addAttachment(ImageView* attachment) {
    m_attachments.push_back(attachment->handle());
}

void Framebuffer::setWidth(uint32_t width) {
    m_createInfo.width = width;
}

void Framebuffer::setHeight(uint32_t height) {
    m_createInfo.height = height;
}

void Framebuffer::setRenderPass(RenderPass* renderPass) {
    m_createInfo.renderPass = renderPass->handle();
}

}
