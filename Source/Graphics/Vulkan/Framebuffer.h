#pragma once
#include "Base/Handle.h"
#include "Device/Device.h"
#include "RenderPass.h"
#include "Image/ImageView.h"

namespace Vulkan {

class Framebuffer : public Handle<VkFramebuffer> {

public:
    Framebuffer(const Device* device, const RenderPass* renderPass, ImageView* imageView, VkExtent2D extent);
    ~Framebuffer();
    VkResult create() override;

private:
    const Device* device;
    ImageView* imageView;
    VkFramebufferCreateInfo createInfo = {};
};

} // Vulkan
