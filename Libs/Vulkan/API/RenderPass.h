#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
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
    VkFormat getColorFormat() const { return colorAttachmentDescription.format; }

    void setDepthFormat(VkFormat format);
    VkFormat getDepthFormat() const { return depthAttachmentDescription.format; }

    void setDepthEnable(bool depthEnable);

private:
    VkRenderPassCreateInfo createInfo = {};
    VkAttachmentDescription colorAttachmentDescription = {};
    VkAttachmentDescription depthAttachmentDescription = {};
    VkAttachmentReference colorAttachmentReference = {};
    VkAttachmentReference depthAttachmentReference = {};
    VkSubpassDescription subpassDescription = {};
    std::vector<VkSubpassDependency> subpassDependencies;
    std::vector<VkSubpassDescription> subpassDescriptions;
    std::vector<VkAttachmentDescription> attachmentDescriptions;
    bool depthEnable = false;
};

} // Vulkan
