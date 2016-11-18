#include "Swapchain.h"

using namespace Vulkan;

Swapchain::Swapchain(const Device* device, const Surface* surface) : device(device) {
    VkSurfaceCapabilitiesKHR capabilities = {};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->getPhysicalDevices()->getPrimary(), surface->getHandle(), &capabilities);
    uint32_t imageCount = capabilities.minImageCount + 1;

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.flags = 0;
    createInfo.surface = surface->getHandle();
//    createInfo.minImageCount = imageCount;
//    createInfo.imageFormat =
//    createInfo.imageColorSpace =
//    createInfo.imageExtent =
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
//    createInfo.imageSharingMode =
//    createInfo.queueFamilyIndexCount =
//    createInfo.pQueueFamilyIndices =
//    createInfo.preTransform =
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//    createInfo.presentMode =
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    result = vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle);
    print(handle);

    vkGetSwapchainImagesKHR(device->getHandle(), handle, &imageCount, nullptr);
    images.resize(imageCount);
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &imageCount, images.data());
}

Swapchain::~Swapchain() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
    }
}
