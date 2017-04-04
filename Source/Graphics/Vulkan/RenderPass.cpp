#include "RenderPass.h"
#include "Manager.h"

using namespace Vulkan;

RenderPass::RenderPass(const Device* device) :
    Devicer(device) {
    beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginInfo.renderArea.offset = { 0, 0 };
    beginInfo.renderArea.extent = Vulkan::Manager::get()->getSurface()->getCapabilities().currentExtent;
}

RenderPass::~RenderPass() {
    destroy();
}

void RenderPass::create() {
    colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachmentDescription.loadOp = overlayEnable ? VK_ATTACHMENT_LOAD_OP_LOAD : VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    attachmentDescriptions.push_back(colorAttachmentDescription);

    if (depthEnable) {
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

    // Use subpass dependencies for image layout transitions
    if (overlayEnable) {
        // Transition from final to initial (VK_SUBPASS_EXTERNAL refers to all commmands executed outside of the actual renderpass)
        VkSubpassDependency subpassDependency0;
        subpassDependency0.srcSubpass = VK_SUBPASS_EXTERNAL;
        subpassDependency0.dstSubpass = 0;
        subpassDependency0.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        subpassDependency0.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency0.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        subpassDependency0.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        subpassDependency0.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

        subpassDependencies.push_back(subpassDependency0);

        // Transition from initial to final
        VkSubpassDependency subpassDependency1;
        subpassDependency1.srcSubpass = 0;
        subpassDependency1.dstSubpass = VK_SUBPASS_EXTERNAL;
        subpassDependency1.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        subpassDependency1.dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        subpassDependency1.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        subpassDependency1.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        subpassDependency1.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

        subpassDependencies.push_back(subpassDependency1);
    }

    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo.attachmentCount = attachmentDescriptions.size();
    createInfo.pAttachments = attachmentDescriptions.data();
    createInfo.subpassCount = subpassDescriptions.size();
    createInfo.pSubpasses = subpassDescriptions.data();
    createInfo.dependencyCount = subpassDependencies.size();
    createInfo.pDependencies = subpassDependencies.data();
    CHECK_RESULT(vkCreateRenderPass(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create render pass");
    beginInfo.renderPass = handle;
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

void RenderPass::setOverlayEnable(bool overlayEnable) {
    this->overlayEnable = overlayEnable;
}

void RenderPass::addClearValue(VkClearValue clearValue) {
    clearValues.push_back(clearValue);
    beginInfo.clearValueCount = clearValues.size();
    beginInfo.pClearValues = clearValues.data();
}

void RenderPass::setClearValue(VkClearValue clearValue) {
    clearValues.clear();
    addClearValue(clearValue);
}
