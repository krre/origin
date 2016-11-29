#include "SurfaceFormat.h"

using namespace Vulkan;

SurfaceFormat::SurfaceFormat(VkPhysicalDevice physicalDevice, const Surface* surface) :
    physicalDevice(physicalDevice),
    surface(surface) {

    uint32_t count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface->getHandle(), &count, nullptr);
    formats.resize(count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface->getHandle(), &count, formats.data());
}
