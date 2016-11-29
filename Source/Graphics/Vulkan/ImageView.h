#pragma once
#include "VkObject.h"
#include "Device.h"
#include "SurfaceFormat.h"

namespace Vulkan {

class ImageView : public VkObject {

public:
    ImageView(const Device* device, const Surface* surface, VkImage image);
    ~ImageView();
    VkImageView getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkImageView handle = VK_NULL_HANDLE;
    const Device* device;
    const Surface* surface;
};

} // Vulkan
