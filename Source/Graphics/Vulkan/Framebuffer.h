#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class Framebuffer : public VkObject {

public:
    Framebuffer(const Device* device);
    ~Framebuffer();
    VkFramebuffer getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkFramebuffer handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
