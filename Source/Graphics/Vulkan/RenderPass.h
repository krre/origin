#pragma once
#include "Base/Handle.h"
#include "Device.h"
#include "Surface.h"

namespace Vulkan {

class RenderPass : public Handle<VkRenderPass> {

public:
    RenderPass(const Device* device, const Surface* surface);
    ~RenderPass();
    bool create() override;

private:
    const Device* device;
    const Surface* surface;
    VkRenderPassCreateInfo createInfo = {};
    VkAttachmentDescription colorAttachment = {};
    VkAttachmentReference colorAttachmentRef = {};
    VkSubpassDescription subPass = {};
};

} // Vulkan
