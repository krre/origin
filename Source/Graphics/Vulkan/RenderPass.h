#pragma once
#include "VkObject.h"
#include "Device.h"
#include "SurfaceFormat.h"

namespace Vulkan {

class RenderPass : public VkObject {

public:
    RenderPass(const Device* device, const SurfaceFormat* surfaceFormat);
    ~RenderPass();
    VkRenderPass getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkRenderPass handle = VK_NULL_HANDLE;
    const Device* device;
    const SurfaceFormat* surfaceFormat;
};

} // Vulkan
