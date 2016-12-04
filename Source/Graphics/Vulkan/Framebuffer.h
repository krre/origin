#pragma once
#include "Base/CreatableObject.h"
#include "Device.h"
#include "RenderPass.h"
#include "ImageView.h"

namespace Vulkan {

class Framebuffer : public CreatableObject<VkFramebuffer> {

public:
    Framebuffer(const Device* device, const RenderPass* renderPass, ImageView* imageView, VkExtent2D extent);
    ~Framebuffer();
    bool create() override;

private:
    const Device* device;
    ImageView* imageView;
    VkFramebufferCreateInfo createInfo = {};
};

} // Vulkan
