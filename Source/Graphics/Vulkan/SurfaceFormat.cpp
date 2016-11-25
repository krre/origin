#include "SurfaceFormat.h"

using namespace Vulkan;

SurfaceFormat::SurfaceFormat(const PhysicalDevices* physicalDevices, const Surface* surface) :
    physicalDevices(physicalDevices),
    surface(surface) {

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevices->getPrimary(), surface->getHandle(), &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevices->getPrimary(), surface->getHandle(), &formatCount, formats.data());
    surfaceFormat = formats[0]; // TODO: Select by requirements
}
