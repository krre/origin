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
    void setHeight(uint32_t height);
    void setRenderPass(VkRenderPass renderPass);

private:
    VkFramebufferCreateInfo createInfo = {};
    std::vector<VkImageView> attachments;
};

} // Vulkan
