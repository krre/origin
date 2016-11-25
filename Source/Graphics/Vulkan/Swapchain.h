#pragma once
#include "VkObject.h"
#include "Device.h"
#include "Surface.h"
#include "SurfaceFormat.h"
#include <vector>

namespace Vulkan {

class Swapchain : public VkObject {

public:
    Swapchain(const Device* device, const Surface* surface, const SurfaceFormat* surfaceFormat);
    ~Swapchain();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkSwapchainKHR getHandle() const { return handle; }
    std::vector<VkImage>* getImages() { return &images; }

private:
    VkSwapchainKHR handle = VK_NULL_HANDLE;
    const Device* device;
    const Surface* surface;
    std::vector<VkImage> images;
    const SurfaceFormat* surfaceFormat;
};

} // Vulkan
