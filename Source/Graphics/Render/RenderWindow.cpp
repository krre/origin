#include "RenderWindow.h"
#include "Core/Application.h"
#include "Core/SDLWrapper.h"
#include "Core/Settings.h"
#include "Core/Defines.h"
#include "Graphics/Vulkan/Context.h"
#include "Graphics/Vulkan/Surface/Surface.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Surface/Swapchain.h"
#include "Graphics/Vulkan/Queue/PresentQueue.h"
#include "Graphics/Vulkan/Device/PhysicalDevice.h"
#include "Graphics/Vulkan/Device/DeviceMemory.h"
#include "Graphics/Vulkan/RenderPass.h"
#include "Graphics/Vulkan/Framebuffer.h"
#include "Graphics/Vulkan/Semaphore.h"
#include "Graphics/Vulkan/Image/Image.h"
#include "Graphics/Vulkan/Image/ImageView.h"
#include "Graphics/Vulkan/Command/CommandBufferOneTime.h"
#include "Event/Event.h"

// Hack to disable typedef Screen from X11 to prevent conflict with Screen class
#define Screen SCREEN_DEF

#ifdef OS_WIN
    #include "Graphics/Vulkan/Surface/Win32Surface.h"
#elif OS_LINUX
    #include "Graphics/Vulkan/Surface/XcbSurface.h"
#endif

#undef Screen

#include "Core/Game.h"
#include <SDL_syswm.h>
#include <SDL_video.h>
#include <lodepng/lodepng.h>

RenderWindow::RenderWindow() {
    int screenWidth = SDLWrapper::get()->getScreenSize().width;
    int screenHeight = SDLWrapper::get()->getScreenSize().height;

    auto settingsWidth = Settings::get()->getStorage()["width"];
    auto settingsHeigth = Settings::get()->getStorage()["height"];

    width = settingsWidth.is_null() ? WINDOW_WIDTH : settingsWidth.get<int>();
    height = settingsHeigth.is_null() ? WINDOW_HEIGHT : settingsHeigth.get<int>();

    auto settingsX = Settings::get()->getStorage()["x"];
    auto settingsY = Settings::get()->getStorage()["y"];

    x = settingsX.is_null() ? (screenWidth - width) / 2 : settingsX.get<int>();
    y = settingsY.is_null() ? (screenHeight - height) / 2 : settingsY.get<int>();

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

    device = Vulkan::Context::get()->getGraphicsDevice();

#ifdef OS_WIN
    surface = std::make_unique<Vulkan::Win32Surface>(Vulkan::Context::get()->getInstance(), device->getPhysicalDevice(), GetModuleHandle(nullptr), wminfo.info.win.window);
#elif OS_LINUX
    surface = std::make_unique<Vulkan::XcbSurface>(Vulkan::Context::get()->getInstance(), device->getPhysicalDevice(), XGetXCBConnection(wminfo.info.x11.display), wminfo.info.x11.window);
#endif

    surface->create();

    VkExtent2D currentExtent = surface->getCurrentExtent();

    renderPass = std::make_unique<Vulkan::RenderPass>(device);
    renderPass->setColorFormat(surface->getFormats().at(0).format);
    renderPass->setExtent(currentExtent);
    renderPass->create();

    presentQueue = std::make_unique<Vulkan::PresentQueue>(device, Vulkan::Context::get()->getGraphicsFamily());

    createSwapchain();

    imageAvailableSemaphore = std::make_unique<Vulkan::Semaphore>(device);
    imageAvailableSemaphore->create();

    Event::get()->windowMove.connect<RenderWindow, &RenderWindow::onMove>(this);
    Event::get()->windowResize.connect<RenderWindow, &RenderWindow::onResize>(this);
}

RenderWindow::~RenderWindow() {
    int x, y, width, height;

    SDL_GetWindowPosition(handle, &x, &y);
    Settings::get()->getStorage()["x"] = x;
    Settings::get()->getStorage()["y"] = y;

    SDL_GetWindowSize(handle, &width, &height);
    Settings::get()->getStorage()["width"] = width;
    Settings::get()->getStorage()["height"] = height;

    SDL_DestroyWindow(handle);
}

void RenderWindow::show() {
    assert(handle != nullptr);
    SDL_ShowWindow(handle);
}

void RenderWindow::onMove(int x, int y) {

}

void RenderWindow::onResize(int width, int height) {

}

void RenderWindow::createSwapchain() {
    swapchain.reset();
    swapchain = std::make_unique<Vulkan::Swapchain>(device, surface.get());
    swapchain->create();

    presentQueue->clearSwapchains();
    presentQueue->addSwapchain(swapchain.get());

    imageViews.clear();
    framebuffers.clear();

    VkExtent2D currentExtent = surface->getCurrentExtent();

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
}

void RenderWindow::saveImage(const std::string& filePath) {
    VkImage srcImage = swapchain->getCurrentImage();

    uint32_t width = surface->getCurrentExtent().width;
    uint32_t height = surface->getCurrentExtent().height;

    Vulkan::Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    Vulkan::CommandBufferOneTime commandBuffer(device, Vulkan::Context::get()->getGraphicsCommandPool());
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

void RenderWindow::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(handle) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(handle, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void RenderWindow::acquireNextImage() {
    VkResult result = swapchain->acquireNextImage(imageAvailableSemaphore.get());
    if (result != VK_SUCCESS) {
        rebuild();
    }
}

void RenderWindow::present() {
    presentQueue->present();
}

void RenderWindow::rebuild() {
    VkExtent2D currentExtent = surface->getCurrentExtent();
    renderPass->setExtent(currentExtent);
    createSwapchain();
    Game::get()->resize(currentExtent.width, currentExtent.height);
}
