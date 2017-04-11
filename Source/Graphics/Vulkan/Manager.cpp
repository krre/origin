#include "Manager.h"
#include "Image/Image.h"
#include "../../Core/App.h"
#include "Command/CommandBufferOneTime.h"
#include "../../Event/Event.h"
#include "../../Scene/SceneManager.h"
#include <glm/glm.hpp>
#include <fstream>
#include <lodepng/lodepng.h>

using namespace Vulkan;

Manager::~Manager() {
    presentQueue.reset();
    imageAvailableSemaphore.reset();
    swapchain.reset();
    renderPass.reset();
    commandPool.reset();
    Instance::get()->release();
}

void Manager::init() {
    new Instance();
    Instance* instance = Instance::get();
    instance->create();

    device = instance->getDefaultDevice();

    commandPool = std::make_shared<CommandPool>(instance->getGraphicsFamily());
    commandPool->create();

    renderPass = std::make_shared<RenderPass>(device);
    renderPass->setColorFormat(instance->getSurface()->getFormats().at(0).format);
    renderPass->create();

    swapchain = std::make_shared<Swapchain>(instance->getSurface());
    swapchain->create();

    imageAvailableSemaphore = std::make_shared<Semaphore>(device);
    imageAvailableSemaphore->create();

    presentQueue = std::make_shared<PresentQueue>(instance->getGraphicsFamily());
    presentQueue->addSwapchain(swapchain->getHandle());

    Event::get()->windowResize.connect<Manager, &Manager::onWindowResize>(this);
}

void Manager::renderBegin() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, presentQueue->getImageIndex(swapchain->getIndex()));
}

void Manager::renderEnd() {
    presentQueue->present();
}

void Manager::saveScreenshot(const std::string& filePath) {
    VkImage srcImage = swapchain->getImage(*presentQueue->getImageIndex(swapchain->getIndex()));

    uint32_t width = App::get()->getWidth();
    uint32_t height = App::get()->getHeight();
    Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    CommandBufferOneTime commandBuffer(device);
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

void Manager::onWindowResize(int width, int height) {
    if (App::get()->getIsRunning()) {
        device->waitIdle();
        swapchain->destroy();
        swapchain->create();
        presentQueue->clearSwapchain();
        presentQueue->addSwapchain(swapchain->getHandle());
        commandPool->reset();
        SceneManager::get()->rebuild();
    }
}
