#include "Swapchain.h"
#include "Surface.h"
#include "../device/PhysicalDevice.h"
#include "../Semaphore.h"

namespace Vulkan {

Swapchain::Swapchain(Device* device, Surface* surface) :
        Devicer(device),
        m_surface(surface) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    m_createInfo.imageArrayLayers = 1;
    m_createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    m_createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    m_createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    m_createInfo.clipped = VK_TRUE;

    uint32_t queueFamilyIndex = 0; // TODO: Use real index
    bool surfaceSupport = device->physicalDevice()->supportSurface(surface, queueFamilyIndex);
    if (surfaceSupport) {
        m_createInfo.surface = surface->handle();
        m_createInfo.minImageCount = surface->capabilities().minImageCount + 1;
        m_createInfo.imageFormat = surface->formats().at(0).format;
        m_createInfo.imageColorSpace = surface->formats().at(0).colorSpace;
        m_createInfo.preTransform = surface->capabilities().currentTransform;
        m_createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    }
}

Swapchain::~Swapchain() {
    destroy();
}

void Swapchain::create() {
    m_createInfo.imageExtent = m_surface->currentExtent();;
//    createInfo.oldSwapchain = handle;
    VULKAN_CHECK_RESULT(vkCreateSwapchainKHR(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create swapchain");

    uint32_t count;
    vkGetSwapchainImagesKHR(m_device->handle(), m_handle, &count, nullptr);
    m_images.resize(count);
    vkGetSwapchainImagesKHR(m_device->handle(), m_handle, &count, m_images.data());
}

void Swapchain::destroy() {
    m_device->waitIdle();
    VULKAN_DESTROY_HANDLE(vkDestroySwapchainKHR(m_device->handle(), m_handle, nullptr))
}

VkResult Swapchain::acquireNextImage(Semaphore* semaphore) {
    return vkAcquireNextImageKHR(m_device->handle(), m_handle, UINT64_MAX, semaphore->handle(), VK_NULL_HANDLE, m_imageIndex);
}

VkResult Swapchain::acquireNextImage(Semaphore* semaphore, uint32_t* index) {
    return vkAcquireNextImageKHR(m_device->handle(), m_handle, UINT64_MAX, semaphore->handle(), VK_NULL_HANDLE, index);
}

void Swapchain::setImageIndexPtr(uint32_t* pImageIndex) {
    this->m_imageIndex = pImageIndex;
}

}
