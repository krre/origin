#include "RenderPass.h"
#include "Instance.h"

namespace Vulkan {

RenderPassBegin::RenderPassBegin(VkRenderPass renderPass) {
    beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginInfo.renderPass = renderPass;
}

void RenderPassBegin::setFrameBuffer(VkFramebuffer framebuffer) {
    beginInfo.framebuffer = framebuffer;
}

void RenderPassBegin::setRenderArea(VkRect2D renderArea) {
    beginInfo.renderArea = renderArea;
}

void RenderPassBegin::addClearValue(VkClearValue clearValue) {
    clearValues.push_back(clearValue);
    beginInfo.clearValueCount = clearValues.size();
    beginInfo.pClearValues = clearValues.data();
}

RenderPass::RenderPass(Device* device) :
    Devicer(device) {
}

RenderPass::~RenderPass() {
    destroy();
}

void RenderPass::create() {
    m_colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    m_colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    m_colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    m_colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    m_colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    m_colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    m_colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    m_attachmentDescriptions.push_back(m_colorAttachmentDescription);

    if (m_depthEnable) {
        m_depthAttachmentDescription.format = VK_FORMAT_D16_UNORM;
        m_depthAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        m_depthAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        m_depthAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        m_depthAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        m_depthAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        m_depthAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        m_depthAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        m_attachmentDescriptions.push_back(m_depthAttachmentDescription);
    }

    m_colorAttachmentReference.attachment = 0;
    m_colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    if (m_depthEnable) {
        m_depthAttachmentReference.attachment = 1;
        m_depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    m_subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    m_subpassDescription.colorAttachmentCount = 1;
    m_subpassDescription.pColorAttachments = &m_colorAttachmentReference;
    if (m_depthEnable) {
        m_subpassDescription.pDepthStencilAttachment = &m_depthAttachmentReference;
    }

    m_subpassDescriptions.push_back(m_subpassDescription);

    m_createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    m_createInfo.attachmentCount = m_attachmentDescriptions.size();
    m_createInfo.pAttachments = m_attachmentDescriptions.data();
    m_createInfo.subpassCount = m_subpassDescriptions.size();
    m_createInfo.pSubpasses = m_subpassDescriptions.data();
    m_createInfo.dependencyCount = m_subpassDependencies.size();
    m_createInfo.pDependencies = m_subpassDependencies.data();
    VULKAN_CHECK_RESULT(vkCreateRenderPass(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create render pass");
}

void RenderPass::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyRenderPass(m_device->handle(), m_handle, nullptr))
}

void RenderPass::setColorFormat(VkFormat format) {
    m_colorAttachmentDescription.format = format;
}

void RenderPass::setDepthFormat(VkFormat format) {
    m_depthAttachmentDescription.format = format;
}

void RenderPass::setDepthEnable(bool depthEnable) {
    this->m_depthEnable = depthEnable;
}

}
