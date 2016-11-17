#pragma once
#define VK_USE_PLATFORM_XCB_KHR
#include "VulkanObject.h"
#include "Instance.h"

namespace Vulkan {

class Surface : public VulkanObject {

public:
    Surface(const Instance* instance);
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkSurfaceKHR getHandle() const { return handle; }

private:
    const Instance* instance;
    VkSurfaceKHR handle = VK_NULL_HANDLE;
};

} // Vulkan
