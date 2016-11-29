#pragma once
#include "VkObject.h"
#include "PhysicalDevices.h"
#include "Surface.h"

namespace Vulkan {

class SurfaceFormat : public VkObject {

public:
    SurfaceFormat(VkPhysicalDevice physicalDevice, const Surface* surface);
    const VkSurfaceFormatKHR* getSurfaceFormat() const { return &surfaceFormat; }

private:
    VkPhysicalDevice physicalDevice;
    const Surface* surface;
    VkSurfaceFormatKHR surfaceFormat;
};

} // Vulkan
