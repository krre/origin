#pragma once
#include "Device/Devicer.h"
#include "Surface.h"

namespace Vulkan {

class RenderPass : public Devicer<VkRenderPass> {

public:
    RenderPass(const Device* device, const Surface* surface);
    ~RenderPass();
    VkResult create() override;
    void destroy() override;

private:
    const Surface* surface;
    VkRenderPassCreateInfo createInfo = {};
    VkAttachmentDescription colorAttachment = {};
    VkAttachmentReference colorAttachmentRef = {};
    VkSubpassDescription subPass = {};
};

} // Vulkan
