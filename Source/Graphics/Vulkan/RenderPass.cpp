#include "RenderPass.h"

using namespace Vulkan;

RenderPass::RenderPass(const Device* device) :
    Devicer(device) {
}

RenderPass::~RenderPass() {
    destroy();
}

VkResult RenderPass::create() {
    std::vector<VkAttachmentDescription> attachments;

    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = depthEnable ? VK_ATTACHMENT_LOAD_OP_LOAD : VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    attachments.push_back(colorAttachment);

    if (depthEnable) {
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        attachments.push_back(depthAttachment);
    }

    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    if (depthEnable) {
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }

    subPassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subPassDescription.colorAttachmentCount = 1;
    subPassDescription.pColorAttachments = &colorAttachmentRef;
    if (depthEnable) {
        subPassDescription.pDepthStencilAttachment = &depthAttachmentRef;
    }

    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();
    createInfo.subpassCount = 1;
    createInfo.pSubpasses = &subPassDescription;
    return checkError(vkCreateRenderPass(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create render pass");
}

void RenderPass::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyRenderPass(device->getHandle(), handle, nullptr))
}

void RenderPass::setColorFormat(VkFormat format) {
    colorAttachment.format = format;
}

void RenderPass::setDepthFormat(VkFormat format) {
    depthAttachment.format = format;
}

void RenderPass::setDepthEnable(bool depthEnable) {
    this->depthEnable = depthEnable;
}
