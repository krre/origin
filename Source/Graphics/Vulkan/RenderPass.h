#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "Surface.h"

namespace Vulkan {

class RenderPass : public Handle<VkRenderPass>, public Devicer {

public:
    RenderPass(const Device* device);
    ~RenderPass();
    VkResult create() override;
    void destroy() override;
    void setFormat(VkFormat format);

private:
    VkRenderPassCreateInfo createInfo = {};
    VkAttachmentDescription colorAttachment = {};
    VkAttachmentReference colorAttachmentRef = {};
    VkSubpassDescription subPass = {};
};

} // Vulkan
