#include "Swapchain.h"
#include "Surface.h"
#include "../Device/PhysicalDevice.h"
#include "../Semaphore.h"

using namespace Vulkan;

Swapchain::Swapchain(Device* device, Surface* surface) :
        Devicer(device),
        surface(surface) {
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;

    uint32_t queueFamilyIndex = 0; // TODO: Use real index
    bool surfaceSupport = device->getPhysicalDevice()->getSupportSurface(surface, queueFamilyIndex);
    if (surfaceSupport) {
        createInfo.surface = surface->getHandle();
        createInfo.minImageCount = surface->getCapabilities().minImageCount + 1;
        createInfo.imageFormat = surface->getFormats().at(0).format;
        createInfo.imageColorSpace = surface->getFormats().at(0).colorSpace;
        createInfo.preTransform = surface->getCapabilities().currentTransform;
        createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    }
}

Swapchain::~Swapchain() {
    destroy();
}

void Swapchain::create() {
    createInfo.imageExtent = surface->getCurrentExtent();;
//    createInfo.oldSwapchain = handle;
    VULKAN_CHECK_RESULT(vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create swapchain");

    uint32_t count;
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, nullptr);
    images.resize(count);
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, images.data());
}

void Swapchain::destroy() {
    device->waitIdle();
    VULKAN_DESTROY_HANDLE(vkDestroySwapchainKHR(device->getHandle(), handle, nullptr))
}

VkResult Swapchain::acquireNextImage(Semaphore* semaphore) {
    return vkAcquireNextImageKHR(device->getHandle(), handle, UINT64_MAX, semaphore->getHandle(), VK_NULL_HANDLE, pImageIndex);
}

VkResult Swapchain::acquireNextImage(Semaphore* semaphore, uint32_t* index) {
    return vkAcquireNextImageKHR(device->getHandle(), handle, UINT64_MAX, semaphore->getHandle(), VK_NULL_HANDLE, index);
}

void Swapchain::setImageIndexPtr(uint32_t* pImageIndex) {
    this->pImageIndex = pImageIndex;
}

