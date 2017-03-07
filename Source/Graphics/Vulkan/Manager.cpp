#include "Manager.h"
#include "Image/Image.h"
#include "../../Core/App.h"
#include "Command/CommandBuffer.h"
#include "Pipeline/PipelineBarrier.h"
#include "Fence.h"
#include <glm/glm.hpp>
#include <fstream>
#include <lodepng/lodepng.h>

using namespace Vulkan;

Manager::~Manager() {
    delete presentQueue;
    delete graphicsQueue;
    delete renderFinishedSemaphore;
    delete imageAvailableSemaphore;
    framebuffers.clear();
    delete renderPass;
    imageViews.clear();
    delete swapchain;
    delete surface;
    delete commandPool;
    delete device;
    delete physicalDevices;
    delete debugCallback;
    delete instance;
}

bool Manager::init() {
    instance = new Instance();
    instance->setEnabledLayers({
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
    if (instance->create() != VK_SUCCESS) {
        return false;
    }

    if (enableValidationLayers) {
        debugCallback = new DebugReportCallback(instance);
        if (debugCallback->create() != VK_SUCCESS) {
            return false;
        }
    }

    physicalDevices = new PhysicalDevices(instance);
    mainPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (mainPhysicalDevice == nullptr) {
        mainPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsFamily = mainPhysicalDevice->findQueue(VK_QUEUE_GRAPHICS_BIT);

    device = new Device(mainPhysicalDevice, graphicsFamily);
    if (device->create() != VK_SUCCESS) {
        return false;
    }

    commandPool = new CommandPool(device, graphicsFamily);
    if (commandPool->create() != VK_SUCCESS) {
        return false;
    }
    commandPool->reset();

    surface = new Surface(instance, mainPhysicalDevice->getHandle());
    if (surface->create() != VK_SUCCESS) {
        return false;
    }

    swapchain = new Swapchain(device, surface);
    if (swapchain->create() != VK_SUCCESS) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device, swapchain->getImage(i)));
        imageView->createInfo.format = surface->getFormat(0).format;
        if (imageView->create() != VK_SUCCESS) {
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass = new RenderPass(device);
    renderPass->setColorFormat(surface->getFormat(0).format);
    if (renderPass->create() != VK_SUCCESS) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device, renderPass, swapchain->getExtent()));
        framebuffer->addAttachment(imageViews.at(i)->getHandle());
        if (framebuffer->create() != VK_SUCCESS) {
            return false;
        }
        framebuffers.push_back(framebuffer);
    }

    imageAvailableSemaphore = new Semaphore(device);
    if (imageAvailableSemaphore->create() != VK_SUCCESS) {
        return false;
    }

    renderFinishedSemaphore = new Semaphore(device);
    if (renderFinishedSemaphore->create() != VK_SUCCESS) {
        return false;
    }

    graphicsQueue = new SubmitQueue(device, graphicsFamily);
    graphicsQueue->addSignalSemaphore(renderFinishedSemaphore->getHandle());
    graphicsQueue->addWaitSemaphore(imageAvailableSemaphore->getHandle());
    graphicsQueue->setWaitDstStageMask({ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT });

    presentQueue = new PresentQueue(device, 0, 0); // TODO: Set family index and queue index
    presentQueue->addWaitSemaphore(renderFinishedSemaphore->getHandle());
    presentQueue->addSwapchain(swapchain->getHandle());
    presentQueue->presentInfo.pImageIndices = &swapchainImageIndex;

    return true;
}

void Manager::setCommandBuffers(uint32_t count, const VkCommandBuffer* data) {
    graphicsQueue->setCommandBuffers(count, data);
}

void Manager::setCommandBuffers(const CommandBuffers* commandBuffers) {
    graphicsQueue->setCommandBuffers(commandBuffers->getCount(), commandBuffers->getData());
}

void Manager::renderBegin() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, &swapchainImageIndex);
}

void Manager::renderEnd() {
    presentQueue->present();
}

void Manager::submit() {
    graphicsQueue->submit();
}

void Manager::saveScreenshot(const std::string& filePath) {
    VkImage srcImage = swapchain->getImage(swapchainImageIndex);

    uint32_t width = App::get()->getWidth();
    uint32_t height = App::get()->getHeight();
    Image image(device, width, height);
    image.create();
    VkImage dstImage = image.getHandle();

    CommandBuffers commandBuffers(device, commandPool);
    commandBuffers.allocate(1);

    CommandBuffer commandBuffer(commandBuffers.at(0));
    commandBuffer.begin();

    // Transition destination image to transfer destination layout
    VkImageMemoryBarrier imageMemoryBarrier = PipelineBarrier::createImageMemoryBarrier();
    imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imageMemoryBarrier.image = dstImage;
    imageMemoryBarrier.srcAccessMask = 0;
    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    PipelineBarrier pipelineBarrier;
    pipelineBarrier.addImageMemoryBarrier(imageMemoryBarrier);
    commandBuffer.pipelineBarrier(&pipelineBarrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

    // Transition swapchain image from present to transfer source layout
    imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    imageMemoryBarrier.image = srcImage;
    imageMemoryBarrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    pipelineBarrier.clearImageMemoryBarriers();
    pipelineBarrier.addImageMemoryBarrier(imageMemoryBarrier);
    commandBuffer.pipelineBarrier(&pipelineBarrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

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

    // Issue the blit command
    vkCmdBlitImage(commandBuffer.getHandle(),  srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,  1, &imageBlitRegion,  VK_FILTER_NEAREST);

    // Transition destination image to general layout, which is the required layout for mapping the image memory later on
    imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    imageMemoryBarrier.image = dstImage;
    imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    imageMemoryBarrier.dstAccessMask = 0;
    pipelineBarrier.clearImageMemoryBarriers();
    pipelineBarrier.addImageMemoryBarrier(imageMemoryBarrier);
    commandBuffer.pipelineBarrier(&pipelineBarrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

    // Transition back the swapchain image after the blit is done
    imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    imageMemoryBarrier.image = srcImage;
    imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    imageMemoryBarrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
    pipelineBarrier.clearImageMemoryBarriers();
    pipelineBarrier.addImageMemoryBarrier(imageMemoryBarrier);
    commandBuffer.pipelineBarrier(&pipelineBarrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

    commandBuffer.end();

    Fence fence(device);
    fence.create();

    SubmitQueue queue(device, graphicsFamily);
    queue.setCommandBuffers({ commandBuffer.getHandle() });
    queue.submit(fence.getHandle());

    device->waitForFences({ fence.getHandle() });

    // Get layout of the image (including row pitch)
    VkImageSubresource subResource = {};
    subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    VkSubresourceLayout subResourceLayout;
    vkGetImageSubresourceLayout(device->getHandle(), dstImage, &subResource, &subResourceLayout);

    // Map image memory so we can start copying from it
    const unsigned char* data;
    image.getMemory()->map(VK_WHOLE_SIZE, 0, (void**)&data);
    data += subResourceLayout.offset;

    lodepng::encode(filePath, data, width, height);

    image.getMemory()->unmap();
}
