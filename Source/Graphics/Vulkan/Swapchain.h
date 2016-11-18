#pragma once
#include "VulkanObject.h"
#include "Device.h"
#include "Surface.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Swapchain : public VulkanObject {

public:
    Swapchain(const Device* device, const Surface* surface);
    ~Swapchain();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkSwapchainKHR getHandle() const { return handle; }

private:
    VkSwapchainKHR handle = VK_NULL_HANDLE;
    const Device* device;
    const Surface* surface;
};

} // Vulkan
