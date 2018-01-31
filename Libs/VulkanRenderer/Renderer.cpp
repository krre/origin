#include "Renderer.h"
#include "API/Command/CommandBuffer.h"
#include "API/Command/CommandBuffers.h"
#include "API/Command/CommandPool.h"
#include "API/Device/Device.h"
#include "API/Device/PhysicalDevice.h"
#include "API/Device/PhysicalDevices.h"
#include "API/Framebuffer.h"
#include "API/Instance.h"
#include "API/Queue.h"
#include "API/RenderPass.h"
#include "API/Semaphore.h"
#include "API/Surface/Swapchain.h"
#include "API/Surface/Surface.h"
#include "API/Instance.h"
#include "API/Surface/Surface.h"
#include "API/Surface/Swapchain.h"
#include "API/Device/PhysicalDevice.h"
#include "API/Device/DeviceMemory.h"
#include "API/RenderPass.h"
#include "API/Framebuffer.h"
#include "API/Semaphore.h"
#include "API/Fence.h"
#include "API/Image/Image.h"
#include "API/Image/ImageView.h"
#include "API/Command/CommandBufferOneTime.h"

namespace Vulkan {

Renderer* Renderer::renderer = nullptr;

Renderer::Renderer(void* platformHandle, void* platformWindow) :
        platformHandle(platformHandle),
        platformWindow(platformWindow) {
    assert(renderer == nullptr);
    renderer = this;
    instance = std::make_unique<Instance>();
}

Renderer::~Renderer() {
    queue->waitIdle();

    if (graphicsDevice) {
        graphicsDevice->waitIdle();
    }
    if (computeDevice) {
        computeDevice->waitIdle();
    }
}

void Renderer::setEnabledLayers(const std::vector<std::string>& enabledLayers) {
    instance->setEnabledLayers(enabledLayers);
}

void Renderer::setEnabledExtensions(const std::vector<std::string>& enabledExtensions) {
    instance->setEnabledExtensions(enabledExtensions);
}

void Renderer::create() {
//    instance->setUseDebugCallback(true); // TODO: Take from debug settings
    instance->create();

    physicalDevices = std::make_unique<PhysicalDevices>(instance.get());

    // Default graphics and compute device are same and first in list of physical devices
    PhysicalDevice* graphicsPhysicalDevice = physicalDevices->getPhysicalDevice(0);
    PhysicalDevice* computePhysicalDevice = physicalDevices->getPhysicalDevice(0);

    if (physicalDevices->getCount() > 1) {
        if (presetDevice != -1) {
            graphicsPhysicalDevice = physicalDevices->getPhysicalDevice(presetDevice);
            computePhysicalDevice = physicalDevices->getPhysicalDevice(1 - presetDevice);
        } else {
            // Select by hardware properties
            graphicsPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
            if (graphicsPhysicalDevice == nullptr) {
                graphicsPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
            }

            computePhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
            if (computePhysicalDevice == nullptr) {
                computePhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
            }
        }
    }

    // Create graphics logical device and command pool
    graphicsFamily = graphicsPhysicalDevice->findQueueFamily(VK_QUEUE_GRAPHICS_BIT);
    graphicsDevice = std::make_unique<Device>(graphicsPhysicalDevice);
    graphicsDevice->addQueueCreateInfo(graphicsFamily, { 1.0 });
    graphicsDevice->create();

    graphicsCommandPool = std::make_shared<CommandPool>(graphicsDevice.get(), graphicsFamily);
    graphicsCommandPool->create();

    // Create compute logical device and command pool
    if (graphicsPhysicalDevice != computePhysicalDevice) {
        computeFamily = computePhysicalDevice->findQueueFamily(VK_QUEUE_COMPUTE_BIT);
        computeDevice = std::make_unique<Device>(computePhysicalDevice);
        computeDevice->addQueueCreateInfo(computeFamily, { 1.0 });
        computeDevice->create();

        computeCommandPool = std::make_shared<CommandPool>(computeDevice.get(), computeFamily);
        computeCommandPool->create();
    }

    device = graphicsDevice.get();

    imageAvailableSemaphore = std::make_unique<Semaphore>(device);
    imageAvailableSemaphore->create();

    renderFinishedSemaphore = std::make_unique<Semaphore>(device);
    renderFinishedSemaphore->create();

    queue = std::make_unique<Queue>(device, graphicsFamily);
    queue->create();
    queue->addPresentWaitSemaphore(renderFinishedSemaphore.get());

    surface = std::make_unique<Surface>(instance.get(), device->getPhysicalDevice(), platformHandle, platformWindow);
    surface->create();

    renderPass = std::make_unique<RenderPass>(device);
    renderPass->setColorFormat(surface->getFormats().at(0).format);
    renderPass->create();

    swapchain = std::make_unique<Swapchain>(device, surface.get());

    resize();
    init();
}

void Renderer::render() {
    preRender();

    VkResult result = swapchain->acquireNextImage(imageAvailableSemaphore.get());
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        resize();
    }

    queue->clearCommandBuffers();
    queue->addCommandBuffer(commandBuffers->at(swapchain->getImageIndex()),
                            renderFinishedSemaphore->getHandle(),
                            imageAvailableSemaphore->getHandle(), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT);
    queue->submit();
    queue->present();
    queue->waitIdle();

    postRender();
}

void Renderer::resize() {
    uint32_t width = surface->getCurrentExtent().width;
    uint32_t height = surface->getCurrentExtent().height;

    swapchain->destroy();
    swapchain->create();
    queue->clearSwapchains();
    queue->addSwapchain(swapchain.get());

    imageViews.clear();
    framebuffers.clear();

    for (const auto& image : swapchain->getImages()) {
        std::unique_ptr<ImageView> imageView = std::make_unique<ImageView>(device, image);
        imageView->setFormat(surface->getFormats().at(0).format);
        imageView->create();

        std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(device);
        framebuffer->addAttachment(imageView.get());
        framebuffer->setRenderPass(renderPass.get());
        framebuffer->setWidth(width);
        framebuffer->setHeight(height);
        framebuffer->create();

        imageViews.push_back(std::move(imageView));
        framebuffers.push_back(std::move(framebuffer));
    }

    if (!commandBuffers) {
        commandBuffers = std::make_unique<CommandBuffers>(device, graphicsCommandPool.get());
        commandBuffers->allocate(swapchain->getCount());
    }

    updateCommandBuffers();
}

std::vector<unsigned char> Renderer::readFramebuffer() {
    VkImage srcImage = swapchain->getCurrentImage();

    uint32_t width = surface->getCurrentExtent().width;
    uint32_t height = surface->getCurrentExtent().height;

    Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.create();
    VkImage dstImage = image.getHandle();

    CommandBufferOneTime commandBuffer(device, graphicsCommandPool.get());
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

    std::vector<unsigned char> output;
    output.resize(width * height * 4);

    if (supportsBlit) {

    } else {
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
    }

//    lodepng::encode(filePath, output.data(), width, height);

    image.getMemory()->unmap();

    return std::move(output);
}

void Renderer::updateCommandBuffers() {
    for (int i = 0; i < commandBuffers->getCount(); i++) {
        CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.reset();
        commandBuffer.begin();
        writeCommandBuffers(&commandBuffer, framebuffers.at(i).get());
        commandBuffer.end();
    }
}

} // Vulkan
