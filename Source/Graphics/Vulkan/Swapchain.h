#pragma once
#include "VulkanObject.h"
#include "Device.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Swapchain : public VulkanObject {

public:
    Swapchain(const Device* device);
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkSwapchainKHR getHandle() const { return handle; }

private:
    VkSwapchainKHR handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
