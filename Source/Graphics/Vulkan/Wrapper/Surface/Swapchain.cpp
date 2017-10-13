#include "Swapchain.h"
#include "Graphics/Vulkan/VulkanCore.h"
#include "../Instance.h"
#include "../Framebuffer.h"
#include "../Semaphore.h"
#include "Surface.h"
#include "../Queue/PresentQueue.h"
#include "../Device/DeviceMemory.h"
#include "../Device/PhysicalDevice.h"
#include "../Image/Image.h"
#include "../Command/CommandBufferOneTime.h"
#include "Graphics/Vulkan/VulkanCore.h"
#include <lodepng/lodepng.h>
#include <limits>

using namespace Vulkan;

int Swapchain::indexCounter = 0;

Swapchain::Swapchain(Device* device, Surface* surface) :
        Devicer(device),
        surface(surface) {
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;

    VkBool32 surfaceSupport;
    vkGetPhysicalDeviceSurfaceSupportKHR(this->device->getPhysicalDevice()->getHandle(), 0, surface->getHandle(), &surfaceSupport);
    if (surfaceSupport) {
        createInfo.surface = surface->getHandle();
        createInfo.minImageCount = surface->getCapabilities().minImageCount + 1;
        createInfo.imageFormat = surface->getFormats().at(0).format;
        createInfo.imageColorSpace = surface->getFormats().at(0).colorSpace;
        createInfo.preTransform = surface->getCapabilities().currentTransform;
        createInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    }

    index = indexCounter++;

    imageAvailableSemaphore = std::make_shared<Semaphore>();
    imageAvailableSemaphore->create();

    presentQueue = std::make_shared<PresentQueue>(device, VulkanCore::get()->getGraphicsFamily());

    renderPass = std::make_shared<RenderPass>();
    renderPass->setColorFormat(surface->getFormats().at(0).format);
    renderPass->create();
}

Swapchain::~Swapchain() {
    renderPass.reset();
    presentQueue.reset();
    imageAvailableSemaphore.reset();
    destroy();
}

void Swapchain::create() {
    VkExtent2D extent = surface->getCurrentExtent();
    renderPass->setExtent(extent);

    createInfo.imageExtent = extent;
    VULKAN_CHECK_RESULT(vkCreateSwapchainKHR(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create swapchain");

    uint32_t count;
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, nullptr);
    images.resize(count);
    vkGetSwapchainImagesKHR(device->getHandle(), handle, &count, images.data());

    for (const auto& image : images) {
        std::shared_ptr<ImageView> imageView = std::make_shared<ImageView>(image);
        imageView->setFormat(surface->getFormats().at(0).format);
        imageView->create();
        imageViews.push_back(imageView);

        std::shared_ptr<Framebuffer> framebuffer = std::make_shared<Framebuffer>(device);
        framebuffer->addAttachment(imageView->getHandle());
        framebuffer->setRenderPass(renderPass->getHandle());
        framebuffer->setWidth(extent.width);
        framebuffer->setHeight(extent.height);
        framebuffer->create();
        framebuffers.push_back(framebuffer);
    }

    presentQueue->addSwapchain(handle);
}

void Swapchain::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroySwapchainKHR(device->getHandle(), handle, nullptr))
}

void Swapchain::saveImage(const std::string& filePath) {
    VkImage srcImage = images.at(*presentQueue->getImageIndex(index));

    uint32_t width = framebuffers.at(index)->getWidth();
    uint32_t height = framebuffers.at(index)->getHeight();

    Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    CommandBufferOneTime commandBuffer(device, VulkanCore::get()->getGraphicsCommandPool());
    commandBuffer.setImageLayout(dstImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED,
                     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    commandBuffer.setImageLayout(srcImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                     VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

    bool supportsBlit = device->getPhysicalDevice()->getSupportBlit();
    if (supportsBlit) {
        VkOffset3D blitSize;
        blitSize.x = width;
        blitSize.y = height;
        blitSize.z = 1;

        VkImageBlit imageBlitRegion = {};
        imageBlitRegion.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageBlitRegion.srcSubresource.layerCount = 1;
        imageBlitRegion.srcOffsets[1] = blitSize;
        imageBlitRegion.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageBlitRegion.dstSubresource.layerCount = 1;
        imageBlitRegion.dstOffsets[1] = blitSize;

        commandBuffer.addBlitRegion(imageBlitRegion);
        commandBuffer.blitImage(srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    } else {
        VkImageCopy imageCopy;
        imageCopy.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageCopy.srcSubresource.mipLevel = 0;
        imageCopy.srcSubresource.baseArrayLayer = 0;
        imageCopy.srcSubresource.layerCount = 1;
        imageCopy.srcOffset = {};
        imageCopy.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageCopy.dstSubresource.mipLevel = 0;
        imageCopy.dstSubresource.baseArrayLayer = 0;
        imageCopy.dstSubresource.layerCount = 1;
        imageCopy.dstOffset = {};
        imageCopy.extent.width = width;
        imageCopy.extent.height = height;
        imageCopy.extent.depth = 1;

        commandBuffer.addImageCopy(imageCopy);
        commandBuffer.copyImage(srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    }

    commandBuffer.setImageLayout(dstImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL,
                     VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_HOST_BIT);
    commandBuffer.apply();

    // Get layout of the image (including row pitch)
    VkImageSubresource subResource = {};
    subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    VkSubresourceLayout subResourceLayout;
    vkGetImageSubresourceLayout(device->getHandle(), dstImage, &subResource, &subResourceLayout);

    // Map image memory so we can start copying from it
    const unsigned char* data;
    image.getMemory()->map((void**)&data, VK_WHOLE_SIZE);
    data += subResourceLayout.offset;

    if (supportsBlit) {
        lodepng::encode(filePath, data, width, height);
    } else {
        std::vector<unsigned char> output;
        output.resize(width * height * 4);
        // Convert from BGR to RGB
        uint32_t offset = 0;
        for (uint32_t y = 0; y < height; y++) {
            unsigned int *row = (unsigned int*)data;
            for (uint32_t x = 0; x < width; x++) {
                output[offset++] = *((char*)row + 2);
                output[offset++] = *((char*)row + 1);
                output[offset++] = *((char*)row);
                output[offset++] = *((char*)row + 3);

                row++;
            }

            data += subResourceLayout.rowPitch;
        }

        lodepng::encode(filePath, output.data(), width, height);
    }

    image.getMemory()->unmap();
}

void Swapchain::acquireNextImage() {
    vkAcquireNextImageKHR(device->getHandle(), handle, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, presentQueue->getImageIndex(index));
}

void Swapchain::rebuild() {
    imageViews.clear();
    framebuffers.clear();
    destroy();
    create();
    presentQueue->clearSwapchain();
    presentQueue->addSwapchain(handle);
}
