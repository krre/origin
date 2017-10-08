#include "Surface.h"
#include "../Instance.h"
#include "Swapchain.h"

using namespace Vulkan;

Surface::Surface(VkPhysicalDevice physicalDevice) :
    physicalDevice(physicalDevice) {
}

Surface::~Surface() {
    swapchain.reset();
    destroy();
}

void Surface::create() {
    platformCreateHandle();

    uint32_t count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, handle, &count, nullptr);
    formats.resize(count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, handle, &count, formats.data());

    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, handle, &count, nullptr);
    presentModes.resize(count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, handle, &count, presentModes.data());

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, handle, &capabilities);

    swapchain = std::make_unique<Swapchain>(this);
    swapchain->create();
}

void Surface::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySurfaceKHR(Instance::get()->getHandle(), handle, nullptr))
}

VkExtent2D Surface::getCurrentExtent() const {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, handle, &capabilities);
    return capabilities.currentExtent;
}
