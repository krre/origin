#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "RenderPass.h"
#include "Image/ImageView.h"

namespace Vulkan {

class Framebuffer : public Handle<VkFramebuffer>, public Devicer {

public:
    Framebuffer(const Device* device);
    ~Framebuffer();
    void create() override;
    void destroy() override;
    void addAttachment(VkImageView attachment);

    void setWidth(uint32_t width);
    uint32_t getWidth() const { return createInfo.width; }

    void setHeight(uint32_t height);
    uint32_t getHeight() const { return createInfo.height; }

    void setRenderPass(VkRenderPass renderPass);

private:
    VkFramebufferCreateInfo createInfo = {};
    std::vector<VkImageView> attachments;
};

} // Vulkan
