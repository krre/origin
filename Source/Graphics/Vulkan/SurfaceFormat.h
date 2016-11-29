#pragma once
#include "VkObject.h"
#include "PhysicalDevices.h"
#include "Surface.h"

namespace Vulkan {

class SurfaceFormat : public VkObject {

public:
    SurfaceFormat(VkPhysicalDevice physicalDevice, const Surface* surface);
    int getCount() const { return formats.size(); }
    VkSurfaceFormatKHR getFormat(size_t i) const { return formats.at(i); }

private:
    VkPhysicalDevice physicalDevice;
    const Surface* surface;
    std::vector<VkSurfaceFormatKHR> formats;
};

} // Vulkan
