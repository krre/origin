#pragma once
#include "VkObject.h"
#include "Device.h"
#include "RenderPass.h"
#include "ImageView.h"

namespace Vulkan {

class Framebuffer : public VkObject {

public:
    Framebuffer(const Device* device, const RenderPass* renderPass, ImageView* imageView, VkExtent2D extent);
    ~Framebuffer();
    VkFramebuffer getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkFramebuffer handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
