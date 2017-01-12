#include "Swapchain.h"

using namespace Vulkan;

Swapchain::Swapchain(const Device* device, const Surface* surface) :
    device(device),
    surface(surface) {

    VkBool32 surfaceSupport;
    result = vkGetPhysicalDeviceSurfaceSupportKHR(device->getPhysicalDevice()->getHandle(), 0, surface->getHandle(), &surfaceSupport);
    if (surfaceSupport) {
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface->getHandle();
        createInfo.minImageCount = surface->getCapabilities().minImageCount + 1;
        createInfo.imageFormat = surface->getFormat(0).format;
        createInfo.imageColorSpace = surface->getFormat(0).colorSpace;
        createInfo.imageExtent = surface->getCapabilities().currentExtent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.preTransform = surface->getCapabilities().currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = surface->getPresentMode(0);
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;
    }
}

Swapchain::~Swapchain() {
    vkDestroySwapchainKHR(device->getHandle(), handle, nullptr);
}

VkResult Swapchain::create() {
    VkResult result = checkError(vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create swapchain");

    uint32_t count;
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, nullptr);
    images.resize(count);
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, images.data());

    extent = surface->getCapabilities().currentExtent;

    return result;
}
