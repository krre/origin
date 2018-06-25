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
    colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    attachmentDescriptions.push_back(colorAttachmentDescription);

    if (depthEnable) {
        depthAttachmentDescription.format = VK_FORMAT_D16_UNORM;
        depthAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        depthAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        attachmentDescriptions.push_back(depthAttachmentDescription);
    }

    colorAttachmentReference.attachment = 0;
    colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    if (depthEnable) {
        depthAttachmentReference.attachment = 1;
        depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments = &colorAttachmentReference;
    if (depthEnable) {
        subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;
    }

    subpassDescriptions.push_back(subpassDescription);

    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo.attachmentCount = attachmentDescriptions.size();
    createInfo.pAttachments = attachmentDescriptions.data();
    createInfo.subpassCount = subpassDescriptions.size();
    createInfo.pSubpasses = subpassDescriptions.data();
    createInfo.dependencyCount = subpassDependencies.size();
    createInfo.pDependencies = subpassDependencies.data();
    VULKAN_CHECK_RESULT(vkCreateRenderPass(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create render pass");
}

void RenderPass::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyRenderPass(device->getHandle(), handle, nullptr))
}

void RenderPass::setColorFormat(VkFormat format) {
    colorAttachmentDescription.format = format;
}

void RenderPass::setDepthFormat(VkFormat format) {
    depthAttachmentDescription.format = format;
}

void RenderPass::setDepthEnable(bool depthEnable) {
    this->depthEnable = depthEnable;
}

} // Vulkan
