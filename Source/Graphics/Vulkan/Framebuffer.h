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
    VkResult create() override;
    void destroy() override;
    void addAttachment(VkImageView attachment);
    void setWidth(uint32_t width);
    void setHeight(uint32_t height);

    VkFramebufferCreateInfo createInfo = {};

private:
    std::vector<VkImageView> attachments;
};

} // Vulkan
