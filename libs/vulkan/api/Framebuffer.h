#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"

namespace Vulkan {

class ImageView;
class RenderPass;

class Framebuffer : public Handle<VkFramebuffer>, public Devicer {

public:
    Framebuffer(Device* device);
    ~Framebuffer();

    void create() override;
    void destroy() override;

    void addAttachment(ImageView* attachment);

    void setWidth(uint32_t width);
    uint32_t width() const { return m_createInfo.width; }

    void setHeight(uint32_t height);
    uint32_t height() const { return m_createInfo.height; }

    void setRenderPass(RenderPass* renderPass);

private:
    VkFramebufferCreateInfo m_createInfo = {};
    std::vector<VkImageView> m_attachments;
};

}
