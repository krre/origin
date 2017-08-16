#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include <vector>

namespace Vulkan {

class RenderPass : public Handle<VkRenderPass>, public Devicer {

public:
    RenderPass(Device* device = nullptr);
    ~RenderPass();
    void create() override;
    void destroy() override;
    void setColorFormat(VkFormat format);
    void setDepthFormat(VkFormat format);
    void setDepthEnable(bool depthEnable);
    void setBlendEnable(bool blendEnable);
    void addClearValue(VkClearValue clearValue);
    void setClearValue(VkClearValue clearValue);
    void setExtent(VkExtent2D extent);
    const VkRenderPassBeginInfo* getBeginInfo() const { return &beginInfo; }
    void setFramebuffer(VkFramebuffer framebuffer);

private:
    VkRenderPassCreateInfo createInfo = {};
    VkRenderPassBeginInfo beginInfo = {};
    VkAttachmentDescription colorAttachmentDescription = {};
    VkAttachmentDescription depthAttachmentDescription = {};
    VkAttachmentReference colorAttachmentReference = {};
    VkAttachmentReference depthAttachmentReference = {};
    VkSubpassDescription subpassDescription = {};
    std::vector<VkClearValue> clearValues;
    std::vector<VkSubpassDependency> subpassDependencies;
    std::vector<VkSubpassDescription> subpassDescriptions;
    std::vector<VkAttachmentDescription> attachmentDescriptions;
    bool depthEnable = false;
    bool blendEnable = false;
};

} // Vulkan
