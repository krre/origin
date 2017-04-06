#include "Swapchain.h"
#include "Manager.h"

using namespace Vulkan;

int Swapchain::indexCounter = 0;

Swapchain::Swapchain(const Device* device, const Surface* surface) :
    Devicer(device),
    surface(surface) {
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;

    VkBool32 surfaceSupport;
    vkGetPhysicalDeviceSurfaceSupportKHR(device->getPhysicalDevice()->getHandle(), 0, surface->getHandle(), &surfaceSupport);
    if (surfaceSupport) {
        createInfo.surface = surface->getHandle();
        createInfo.minImageCount = surface->getCapabilities().minImageCount + 1;
        createInfo.imageFormat = surface->getFormat(0).format;
        createInfo.imageColorSpace = surface->getFormat(0).colorSpace;
        createInfo.preTransform = surface->getCapabilities().currentTransform;
        createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    }

    index = indexCounter++;
}

Swapchain::~Swapchain() {
    destroy();
}

void Swapchain::create() {
    VkExtent2D extent = surface->getCurrentExtent();
    createInfo.imageExtent = extent;
    CHECK_RESULT(vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create swapchain");

    uint32_t count;
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, nullptr);
    images.resize(count);
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, images.data());

    for (auto& image : images) {
        std::shared_ptr<ImageView> imageView = std::make_shared<ImageView>(device, image);
        imageView->createInfo.format = surface->getFormat(0).format;
        imageView->create();
        imageViews.push_back(imageView);

        std::shared_ptr<Framebuffer> framebuffer = std::make_shared<Framebuffer>(device);
        framebuffer->addAttachment(imageView->getHandle());
        framebuffer->setRenderPass(Manager::get()->getRenderPass()->getHandle());
        framebuffer->setWidth(extent.width);
        framebuffer->setHeight(extent.height);
        framebuffer->create();
        framebuffers.push_back(framebuffer);
    }
}

void Swapchain::destroy() {
    imageViews.clear();
    framebuffers.clear();
    VULKAN_DESTROY_HANDLE(vkDestroySwapchainKHR(device->getHandle(), handle, nullptr))
}

void Swapchain::rebuild() {
    destroy();
    create();
}
