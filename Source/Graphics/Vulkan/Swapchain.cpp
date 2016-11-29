#include "Swapchain.h"

using namespace Vulkan;

Swapchain::Swapchain(const Device* device, const Surface* surface, const SurfaceFormat* surfaceFormat) :
    device(device),
    surface(surface),
    surfaceFormat(surfaceFormat) {
    VkSurfaceCapabilitiesKHR capabilities = {};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->getPhysicalDevice(), surface->getHandle(), &capabilities);
    uint32_t imageCount = capabilities.minImageCount + 1;

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevice(), surface->getHandle(), &presentModeCount, nullptr);
    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevice(), surface->getHandle(), &presentModeCount, presentModes.data());
    VkPresentModeKHR presentMode = presentModes[0]; // TODO: Select by requirements

    VkBool32 surfaceSupport;
    result = vkGetPhysicalDeviceSurfaceSupportKHR(device->getPhysicalDevice(), 0, surface->getHandle(), &surfaceSupport);
    if (surfaceSupport) {
        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.flags = 0;
        createInfo.surface = surface->getHandle();
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat->getFormat(0).format;
        createInfo.imageColorSpace = surfaceFormat->getFormat(0).colorSpace;
        createInfo.imageExtent = capabilities.currentExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.preTransform = capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        result = vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle);

        vkGetSwapchainImagesKHR(device->getHandle(), handle, &imageCount, nullptr);
        images.resize(imageCount);
        vkGetSwapchainImagesKHR(device->getHandle(), handle, &imageCount, images.data());

        extent = capabilities.currentExtent;
    }
}

Swapchain::~Swapchain() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
    }
}
