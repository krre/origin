#include "SurfaceFormat.h"

using namespace Vulkan;

SurfaceFormat::SurfaceFormat(VkPhysicalDevice physicalDevice, const Surface* surface) :
    physicalDevice(physicalDevice),
    surface(surface) {

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface->getHandle(), &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface->getHandle(), &formatCount, formats.data());
    surfaceFormat = formats[0]; // TODO: Select by requirements
}
