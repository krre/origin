#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "Surface.h"
#include <vector>

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
    void addClearValue(VkClearValue clearValue);

    VkRenderPassCreateInfo createInfo = {};
    VkRenderPassBeginInfo beginInfo = {};

private:
    VkAttachmentDescription colorAttachment = {};
    VkAttachmentDescription depthAttachment = {};
    VkAttachmentReference colorAttachmentRef = {};
    VkAttachmentReference depthAttachmentRef = {};
    VkSubpassDescription subPassDescription = {};
    std::vector<VkClearValue> clearValues;
    bool depthEnable = false;
    bool overlayEnable = false;
};

} // Vulkan
