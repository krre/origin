#pragma once
#include "VkCreatableObject.h"
#include "Device.h"
#include "Surface.h"

namespace Vulkan {

class RenderPass : public VkCreatableObject<VkRenderPass> {

public:
    RenderPass(const Device* device, const Surface* surface);
    ~RenderPass();
    void create() override;

private:
    const Device* device;
    const Surface* surface;
    VkRenderPassCreateInfo createInfo = {};
    VkAttachmentDescription colorAttachment = {};
    VkAttachmentReference colorAttachmentRef = {};
    VkSubpassDescription subPass = {};
};

} // Vulkan
