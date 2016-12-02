#pragma once
#include "CreatableObject.h"
#include "Device.h"
#include "Surface.h"

namespace Vulkan {

class RenderPass : public CreatableObject<VkRenderPass> {

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
