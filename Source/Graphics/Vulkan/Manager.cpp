#include "Manager.h"
#include "Image/Image.h"
#include "../../Core/App.h"
#include "Command/CommandBufferOneTime.h"
#include <glm/glm.hpp>
#include <fstream>
#include <lodepng/lodepng.h>

using namespace Vulkan;

void Manager::init() {
    instance.setEnabledLayers({
//        "VK_LAYER_LUNARG_api_dump",
        "VK_LAYER_LUNARG_parameter_validation",
//        "VK_LAYER_LUNARG_vktrace",
        "VK_LAYER_LUNARG_core_validation",
        "VK_LAYER_LUNARG_screenshot",
        "VK_LAYER_LUNARG_swapchain",
        "VK_LAYER_LUNARG_object_tracker",
        "VK_LAYER_GOOGLE_unique_objects",
        "VK_LAYER_GOOGLE_threading",
        "VK_LAYER_LUNARG_standard_validation"
    });

#ifdef __linux__
    instance.setEnabledExtensions({
        "VK_KHR_surface",
        "VK_KHR_xcb_surface",
        "VK_EXT_debug_report"
    });
#endif

    instance.create();

    if (enableValidationLayers) {
        debugCallback = std::make_shared<DebugReportCallback>(&instance);
        debugCallback->create();
    }

    physicalDevices = std::make_shared<PhysicalDevices>(&instance);
    mainPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (mainPhysicalDevice == nullptr) {
        mainPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsFamily = mainPhysicalDevice->findQueue(VK_QUEUE_GRAPHICS_BIT);

    device = std::make_shared<Device>(mainPhysicalDevice);
    device->addQueueCreateInfo(graphicsFamily, { 1.0 });
    device->create();

    surface = std::make_shared<Surface>(instance.getHandle(), mainPhysicalDevice->getHandle());
    surface->create();

    commandPool = std::make_shared<CommandPool>(device.get(), graphicsFamily);
    commandPool->create();
    commandPool->reset();

    swapchain = std::make_shared<Swapchain>(device.get(), surface.get());
    swapchain->create();

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<ImageView> imageView = std::make_shared<ImageView>(device.get(), swapchain->getImage(i));
        imageView->createInfo.format = surface->getFormat(0).format;
        imageView->create();
        imageViews.push_back(imageView);
    }

    renderPass = std::make_shared<RenderPass>(device.get());
    renderPass->setColorFormat(surface->getFormat(0).format);
    renderPass->create();

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device.get()));
        framebuffer->addAttachment(imageViews.at(i)->getHandle());
        framebuffer->setRenderPass(renderPass->getHandle());
        framebuffer->setWidth(surface->getWidth());
        framebuffer->setHeight(surface->getHeight());
        framebuffer->create();
        framebuffers.push_back(framebuffer);
    }

    imageAvailableSemaphore = std::make_shared<Semaphore>(device.get());
    imageAvailableSemaphore->create();

    presentQueue = std::make_shared<PresentQueue>(device.get(), graphicsFamily);
    presentQueue->addSwapchain(swapchain->getHandle());
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
    Image image(device.get());
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    CommandBufferOneTime commandBuffer(device.get());
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
