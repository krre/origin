#include "Swapchain.h"

using namespace Vulkan;

Swapchain::Swapchain(const Device* device, const Surface* surface) : device(device) {
    VkSurfaceCapabilitiesKHR capabilities = {};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->getPhysicalDevices()->getPrimary(), surface->getHandle(), &capabilities);
    uint32_t imageCount = capabilities.minImageCount + 1;

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevices()->getPrimary(), surface->getHandle(), &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevices()->getPrimary(), surface->getHandle(), &formatCount, formats.data());
    VkSurfaceFormatKHR surfaceFormat = formats[0]; // TODO: Select by requirements

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevices()->getPrimary(), surface->getHandle(), &presentModeCount, nullptr);
    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevices()->getPrimary(), surface->getHandle(), &presentModeCount, presentModes.data());
    VkPresentModeKHR presentMode = presentModes[0]; // TODO: Select by requirements

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.flags = 0;
    createInfo.surface = surface->getHandle();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = capabilities.currentExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

//    result = vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle);

//    vkGetSwapchainImagesKHR(device->getHandle(), handle, &imageCount, nullptr);
//    images.resize(imageCount);
//    vkGetSwapchainImagesKHR(device->getHandle(), handle, &imageCount, images.data());
}

Swapchain::~Swapchain() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
    }
}
