#include "RenderPass.h"

using namespace Vulkan;

RenderPass::RenderPass(const Device* device) : device(device) {
    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.subpassCount = 1;

    result = vkCreateRenderPass(device->getHandle(), &renderPassInfo, nullptr, &handle);
}

RenderPass::~RenderPass() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyRenderPass(device->getHandle(), handle, nullptr);
    }
}
