#pragma once
#include "VkObject.h"
#include "PhysicalDevices.h"
#include "Surface.h"

namespace Vulkan {

class SurfaceFormat : public VkObject {

public:
    SurfaceFormat(const PhysicalDevices* physicalDevices, const Surface* surface);
    const VkSurfaceFormatKHR* getSurfaceFormat() const { return &surfaceFormat; }

private:
    const PhysicalDevices* physicalDevices;
    const Surface* surface;
    VkSurfaceFormatKHR surfaceFormat;
};

} // Vulkan
