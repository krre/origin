#include "RenderWindow.h"
#include "Core/Application.h"
#include "Core/SDLWrapper.h"
#include "Core/Settings.h"
#include "Core/Defines.h"
#include "Graphics/Vulkan/VulkanCore.h"
#include "Graphics/Vulkan/Wrapper/Surface/Surface.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Queue/PresentQueue.h"
#include "Graphics/Vulkan/Wrapper/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Wrapper/Device/DeviceMemory.h"
#include "Graphics/Vulkan/Wrapper/RenderPass.h"
#include "Graphics/Vulkan/Wrapper/Framebuffer.h"
#include "Graphics/Vulkan/Wrapper/Semaphore.h"
#include "Graphics/Vulkan/Wrapper/Image/Image.h"
#include "Graphics/Vulkan/Wrapper/Image/ImageView.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBufferOneTime.h"
#include "Event/Event.h"
#include <SDL_video.h>
#include <stdexcept>
#include <lodepng/lodepng.h>

#ifdef OS_WIN
    #include "Graphics/Vulkan/Wrapper/Surface/Win32Surface.h"
#elif OS_LINUX
    #include "Graphics/Vulkan/Wrapper/Surface/XcbSurface.h"
#endif

#include <SDL_syswm.h>

RenderWindow::RenderWindow() {
    int screenWidth = SDLWrapper::get()->getScreenSize().width;
    int screenHeight = SDLWrapper::get()->getScreenSize().height;

    std::string settingsWidth = Settings::get()->getValue("width");
    std::string settingsHeigth = Settings::get()->getValue("height");

    width = settingsWidth.empty() ? WINDOW_WIDTH : std::stoi(settingsWidth);
    height = settingsHeigth.empty() ? WINDOW_HEIGHT : std::stoi(settingsHeigth);

    std::string settingsX = Settings::get()->getValue("x");
    std::string settingsY = Settings::get()->getValue("y");

    x = settingsX.empty() ? (screenWidth - width) / 2 : std::stoi(settingsX);
    y = settingsY.empty() ? (screenHeight - height) / 2 : std::stoi(settingsY);

    // Check dual monitor, and if current screen width is larger then maximum monitor resolution,
    // then divide it on 2
//    if (screenWidth > mode.w) {
//        screenWidth /= 2;
//    }

    handle = SDL_CreateWindow(APP_NAME, x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }

    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    SDL_GetWindowWMInfo(handle, &wminfo);

    device = VulkanCore::get()->getGraphicsDevice();

#ifdef OS_WIN
    surface = std::make_unique<Vulkan::Win32Surface>(VulkanCore::get()->getInstance(), device->getPhysicalDevice(), GetModuleHandle(nullptr), wminfo.info.win.window);
#elif OS_LINUX
    surface = std::make_unique<Vulkan::XcbSurface>(VulkanCore::get()->getInstance(), device->getPhysicalDevice(), XGetXCBConnection(wminfo.info.x11.display), wminfo.info.x11.window);
#endif

    surface->create();
    VulkanCore::get()->setSurface(surface.get());
    VkExtent2D currentExtent = surface->getCurrentExtent();

    renderPass = std::make_unique<Vulkan::RenderPass>(device);
    renderPass->setColorFormat(surface->getFormats().at(0).format);
    renderPass->setExtent(currentExtent);
    renderPass->create();

    swapchain = std::make_unique<Vulkan::Swapchain>(device, surface.get());
    swapchain->create();
    VulkanCore::get()->setSwapchain(swapchain.get());

    presentQueue = std::make_unique<Vulkan::PresentQueue>(device, VulkanCore::get()->getGraphicsFamily());
    presentQueue->addSwapchain(swapchain.get());

    for (const auto& image : swapchain->getImages()) {
        std::unique_ptr<Vulkan::ImageView> imageView = std::make_unique<Vulkan::ImageView>(device, image);
        imageView->setFormat(surface->getFormats().at(0).format);
        imageView->create();

        std::unique_ptr<Vulkan::Framebuffer> framebuffer = std::make_unique<Vulkan::Framebuffer>(device);
        framebuffer->addAttachment(imageView.get());
        framebuffer->setRenderPass(renderPass.get());
        framebuffer->setWidth(currentExtent.width);
        framebuffer->setHeight(currentExtent.height);
        framebuffer->create();

        imageViews.push_back(std::move(imageView));
        framebuffers.push_back(std::move(framebuffer));
    }

    imageAvailableSemaphore = std::make_unique<Vulkan::Semaphore>(device);
    imageAvailableSemaphore->create();

    Event::get()->windowMove.connect<RenderWindow, &RenderWindow::onMove>(this);
    Event::get()->windowResize.connect<RenderWindow, &RenderWindow::onResize>(this);
}

RenderWindow::~RenderWindow() {
    SDL_DestroyWindow(handle);
}

void RenderWindow::show() {
    assert(handle != nullptr);
    SDL_ShowWindow(handle);
}

void RenderWindow::onMove(int x, int y) {
    Settings::get()->setValue("x", std::to_string(x));
    Settings::get()->setValue("y", std::to_string(y));
}

void RenderWindow::onResize(int width, int height) {
    if (Application::get()->isRunning()) {
//        SceneManager::get()->rebuild();
    }

    Settings::get()->setValue("width", std::to_string(width));
    Settings::get()->setValue("height", std::to_string(height));
}

void RenderWindow::swapBuffers() {
    // TODO: Temporaty disable on Linux.
#ifndef OS_LINUX
    presentQueue->present();
    acquireNextImage();
#endif
}

void RenderWindow::saveImage(const std::string& filePath) {
    VkImage srcImage = swapchain->getImages().at(*presentQueue->getImageIndex(index));

    uint32_t width = framebuffers.at(index)->getWidth();
    uint32_t height = framebuffers.at(index)->getHeight();

    Vulkan::Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    Vulkan::CommandBufferOneTime commandBuffer(device, VulkanCore::get()->getGraphicsCommandPool());
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

void RenderWindow::acquireNextImage() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, presentQueue->getImageIndex(index));
}

void RenderWindow::rebuild() {
    presentQueue->clearSwapchain();
    presentQueue->addSwapchain(swapchain.get());
}
