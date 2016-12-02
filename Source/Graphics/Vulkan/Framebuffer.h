#pragma once
#include "VkCreatableObject.h"
#include "Device.h"
#include "RenderPass.h"
#include "ImageView.h"

namespace Vulkan {

class Framebuffer : public VkCreatableObject<VkFramebuffer> {

public:
    Framebuffer(const Device* device, const RenderPass* renderPass, ImageView* imageView, VkExtent2D extent);
    ~Framebuffer();
    void create() override;

private:
    const Device* device;
    ImageView* imageView;
    VkFramebufferCreateInfo createInfo = {};
};

} // Vulkan
