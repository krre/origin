#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"
#include <vector>

namespace Vulkan {

class RenderPassBegin {
public:
    RenderPassBegin(VkRenderPass renderPass);
    VkRenderPassBeginInfo* getInfo() { return &beginInfo; }

    void setFrameBuffer(VkFramebuffer framebuffer);
    void setRenderArea(VkRect2D renderArea);

    void addClearValue(VkClearValue clearValue);

private:
    VkRenderPassBeginInfo beginInfo = {};
    std::vector<VkClearValue> clearValues;
};

class RenderPass : public Handle<VkRenderPass>, public Devicer {
public:
    RenderPass(Device* device);
    ~RenderPass();

    void create() override;
    void destroy() override;

    void setColorFormat(VkFormat format);
    VkFormat colorFormat() const { return m_colorAttachmentDescription.format; }

    void setDepthFormat(VkFormat format);
    VkFormat depthFormat() const { return m_depthAttachmentDescription.format; }

    void setDepthEnable(bool depthEnable);

private:
    VkRenderPassCreateInfo m_createInfo = {};
    VkAttachmentDescription m_colorAttachmentDescription = {};
    VkAttachmentDescription m_depthAttachmentDescription = {};
    VkAttachmentReference m_colorAttachmentReference = {};
    VkAttachmentReference m_depthAttachmentReference = {};
    VkSubpassDescription m_subpassDescription = {};
    std::vector<VkSubpassDependency> m_subpassDependencies;
    std::vector<VkSubpassDescription> m_subpassDescriptions;
    std::vector<VkAttachmentDescription> m_attachmentDescriptions;
    bool m_depthEnable = false;
};

}
