#include "Surface.h"
#include "../Instance.h"
#include "../Device/PhysicalDevice.h"

namespace Vulkan {

Surface::Surface(Instance* instance, PhysicalDevice* physicalDevice) :
    instance(instance),
    physicalDevice(physicalDevice) {
}

Surface::~Surface() {
    destroy();
}

void Surface::create() {
    platformCreateHandle();

    uint32_t count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->getHandle(), handle, &count, nullptr);
    formats.resize(count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->getHandle(), handle, &count, formats.data());

    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->getHandle(), handle, &count, nullptr);
    presentModes.resize(count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->getHandle(), handle, &count, presentModes.data());

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice->getHandle(), handle, &capabilities);
}

void Surface::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySurfaceKHR(instance->getHandle(), handle, nullptr))
}

VkExtent2D Surface::getCurrentExtent() const {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice->getHandle(), handle, &capabilities);
    return capabilities.currentExtent;
}

} // Vulkan
