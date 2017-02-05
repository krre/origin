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
    void setColorFormat(VkFormat format);
    void setDepthFormat(VkFormat format);
    void setDepthEnable(bool depthEnable);
    void setOverlayEnable(bool overlayEnable);


private:
    VkRenderPassCreateInfo createInfo = {};
    VkAttachmentDescription colorAttachment = {};
    VkAttachmentDescription depthAttachment = {};
    VkAttachmentReference colorAttachmentRef = {};
    VkAttachmentReference depthAttachmentRef = {};
    VkSubpassDescription subPassDescription = {};
    bool depthEnable = false;
    bool overlayEnable = false;
};

} // Vulkan
