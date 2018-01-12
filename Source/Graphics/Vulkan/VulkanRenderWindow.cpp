#include "VulkanRenderWindow.h"
#include "Core/Defines.h"
#include "Graphics/Vulkan/VulkanRenderContext.h"
#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Queue/PresentQueue.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Wrapper/Device/DeviceMemory.h"
#include "Graphics/Vulkan/Wrapper/RenderPass.h"
#include "Graphics/Vulkan/Wrapper/Framebuffer.h"
#include "Graphics/Vulkan/Wrapper/Semaphore.h"
#include "Graphics/Vulkan/Wrapper/Fence.h"
#include "Graphics/Vulkan/Wrapper/Image/Image.h"
#include "Graphics/Vulkan/Wrapper/Image/ImageView.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBufferOneTime.h"
#include "Graphics/Render/RenderManager.h"
#include <lodepng/lodepng.h>
#include <SDL_syswm.h>

#if defined(OS_WIN)
    #include "Graphics/Vulkan/Wrapper/Surface/Win32Surface.h"
#elif defined(OS_LINUX)
    #include "Graphics/Vulkan/Wrapper/Surface/XcbSurface.h"
#endif

namespace Origin {

VulkanRenderWindow::VulkanRenderWindow(VulkanRenderContext* context) : context(context) {
    device = context->getGraphicsDevice();

    presentQueue = std::make_unique<Vulkan::PresentQueue>(device, context->getGraphicsFamily());
    presentQueue->create();

    presentFence = std::make_unique<Vulkan::Fence>(device);
    presentFence->setSignaledBit();
    presentFence->create();

    imageAvailableSemaphore = std::make_unique<Vulkan::Semaphore>(device);
    imageAvailableSemaphore->create();

    renderFinishedSemaphore = std::make_unique<Vulkan::Semaphore>(device);
    renderFinishedSemaphore->create();
    presentQueue->addWaitSemaphore(renderFinishedSemaphore.get());
}

VulkanRenderWindow::~VulkanRenderWindow() {

}

uint32_t VulkanRenderWindow::getImageIndex() const {
    return swapchain->getImageIndex();
}

void VulkanRenderWindow::preRender() {
    presentFence->wait();
    presentFence->reset();

    VkResult result = swapchain->acquireNextImage(imageAvailableSemaphore.get());
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        onResize(surface->getCurrentExtent().width, surface->getCurrentExtent().height);
    }
}

void VulkanRenderWindow::postRender() {
    presentQueue->present();
    vkQueueSubmit(presentQueue->getHandle(), 0, nullptr, presentFence->getHandle());
}

void VulkanRenderWindow::onResize(int width, int height) {
    swapchain->destroy();
    swapchain->create();
    presentQueue->clearSwapchains();
    presentQueue->addSwapchain(swapchain.get());

    imageViews.clear();
    framebuffers.clear();

    for (const auto& image : swapchain->getImages()) {
        std::unique_ptr<Vulkan::ImageView> imageView = std::make_unique<Vulkan::ImageView>(device, image);
        imageView->setFormat(surface->getFormats().at(0).format);
        imageView->create();

        std::unique_ptr<Vulkan::Framebuffer> framebuffer = std::make_unique<Vulkan::Framebuffer>(device);
        framebuffer->addAttachment(imageView.get());
        framebuffer->setRenderPass(renderPass.get());
        framebuffer->setWidth(width);
        framebuffer->setHeight(height);
        framebuffer->create();

        imageViews.push_back(std::move(imageView));
        framebuffers.push_back(std::move(framebuffer));
    }

    renderPass->setExtent({ (uint32_t)width, (uint32_t)height });

    RenderWindow::onResize(width, height);
}

void VulkanRenderWindow::saveScreenshotImpl(const std::string& filePath) {
    VkImage srcImage = swapchain->getCurrentImage();

    uint32_t width = surface->getCurrentExtent().width;
    uint32_t height = surface->getCurrentExtent().height;

    Vulkan::Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    Vulkan::CommandBufferOneTime commandBuffer(device, context->getGraphicsCommandPool());
    commandBuffer.setImageLayout(dstImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED,
                     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    commandBuffer.setImageLayout(srcImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                     VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

    bool supportsBlit = device->getPhysicalDevice()->getSupportBlit(swapchain->getImageFormat());
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

Uint32 VulkanRenderWindow::getSurfaceFlag() const {
    return SDL_WINDOW_VULKAN;
}

void VulkanRenderWindow::initImpl() {
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(handle, &wminfo);

#if defined(OS_WIN)
    surface = std::make_unique<Vulkan::Win32Surface>(context->getInstance(), device->getPhysicalDevice(), GetModuleHandle(nullptr), wminfo.info.win.window);
#elif defined(OS_LINUX)
    surface = std::make_unique<Vulkan::XcbSurface>(context->getInstance(), device->getPhysicalDevice(), XGetXCBConnection(wminfo.info.x11.display), wminfo.info.x11.window);
#endif

    surface->create();

    VkExtent2D currentExtent = surface->getCurrentExtent();

    renderPass = std::make_unique<Vulkan::RenderPass>(device);
    renderPass->setColorFormat(surface->getFormats().at(0).format);
    renderPass->setExtent(currentExtent);
    renderPass->create();

    swapchain = std::make_unique<Vulkan::Swapchain>(device, surface.get());

    onResize(width, height);
}

} // Origin
