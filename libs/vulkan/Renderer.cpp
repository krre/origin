#include "Renderer.h"
#include "api/command/CommandBuffer.h"
#include "api/command/CommandBuffers.h"
#include "api/command/CommandPool.h"
#include "api/device/Device.h"
#include "api/device/PhysicalDevice.h"
#include "api/device/PhysicalDevices.h"
#include "api/Framebuffer.h"
#include "api/Instance.h"
#include "api/Queue.h"
#include "api/RenderPass.h"
#include "api/Semaphore.h"
#include "api/surface/Swapchain.h"
#include "api/surface/Surface.h"
#include "api/Instance.h"
#include "api/surface/Surface.h"
#include "api/surface/Swapchain.h"
#include "api/device/PhysicalDevice.h"
#include "api/device/DeviceMemory.h"
#include "api/RenderPass.h"
#include "api/Framebuffer.h"
#include "api/Semaphore.h"
#include "api/Fence.h"
#include "api/image/Image.h"
#include "api/image/ImageView.h"
#include "api/command/CommandBufferOneTime.h"

namespace Vulkan {

const VkFormat depthFormat = VK_FORMAT_D16_UNORM;

Renderer::Renderer(void* platformHandle, void* platformWindow) :
        platformHandle(platformHandle),
        platformWindow(platformWindow) {
    m_instance = std::make_unique<Instance>();
}

Renderer::~Renderer() {
    queue->waitIdle();

    if (m_graphicsDevice) {
        m_graphicsDevice->waitIdle();
    }
    if (m_computeDevice) {
        m_computeDevice->waitIdle();
    }
}

void Renderer::useDebugReport(VkDebugReportFlagsEXT flags) {
    m_instance->useDebugReport(flags);
}

void Renderer::setEnabledLayers(const std::vector<std::string>& enabledLayers) {
    m_instance->setEnabledLayers(enabledLayers);
}

void Renderer::setEnabledExtensions(const std::vector<std::string>& enabledExtensions) {
    m_instance->setEnabledExtensions(enabledExtensions);
}

void Renderer::create() {
    m_instance->create();

    physicalDevices = std::make_unique<PhysicalDevices>(m_instance.get());

    // Default graphics and compute device are same and first in list of physical devices
    PhysicalDevice* graphicsPhysicalDevice = physicalDevices->physicalDevice(0);
    PhysicalDevice* computePhysicalDevice = physicalDevices->physicalDevice(0);

    if (physicalDevices->count() > 1) {
        if (presetDevice != -1) {
            graphicsPhysicalDevice = physicalDevices->physicalDevice(presetDevice);
            computePhysicalDevice = physicalDevices->physicalDevice(1 - presetDevice);
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
    m_graphicsDevice = std::make_unique<Device>(graphicsPhysicalDevice);
    m_graphicsDevice->addQueueCreateInfo(graphicsFamily, { 1.0 });
    m_graphicsDevice->create();

    m_graphicsCommandPool = std::make_shared<CommandPool>(m_graphicsDevice.get(), graphicsFamily);
    m_graphicsCommandPool->create();

    // Create compute logical device and command pool
    if (graphicsPhysicalDevice != computePhysicalDevice) {
        computeFamily = computePhysicalDevice->findQueueFamily(VK_QUEUE_COMPUTE_BIT);
        m_computeDevice = std::make_unique<Device>(computePhysicalDevice);
        m_computeDevice->addQueueCreateInfo(computeFamily, { 1.0 });
        m_computeDevice->create();

        m_computeCommandPool = std::make_shared<CommandPool>(m_computeDevice.get(), computeFamily);
        m_computeCommandPool->create();
    }

    device = m_graphicsDevice.get();

    imageAvailableSemaphore = std::make_unique<Semaphore>(device);
    imageAvailableSemaphore->create();

    renderFinishedSemaphore = std::make_unique<Semaphore>(device);
    renderFinishedSemaphore->create();

    queue = std::make_unique<Queue>(device, graphicsFamily);
    queue->create();
    queue->addPresentWaitSemaphore(renderFinishedSemaphore->handle());

    m_surface = std::make_unique<Surface>(m_instance.get(), device->physicalDevice(), platformHandle, platformWindow);
    m_surface->create();

    m_renderPass = std::make_unique<RenderPass>(device);
    m_renderPass->setColorFormat(m_surface->formats().at(0).format);
//    renderPass->setBlendEnable(true);
    m_renderPass->setDepthEnable(true);
    m_renderPass->setDepthFormat(depthFormat);
    m_renderPass->create();

    swapchain = std::make_unique<Swapchain>(device, m_surface.get());

    resize();
    init();
}

void Renderer::render() {
    preRender();

    VkResult result = swapchain->acquireNextImage(imageAvailableSemaphore.get());
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        resize();
    }

    if (dirty) {
        buildCommandBuffers();
        dirty = false;
    }

    queue->clearCommandBuffers();
    queue->addCommandBuffer(commandBuffers->at(swapchain->imageIndex()),
                            renderFinishedSemaphore->handle(),
                            imageAvailableSemaphore->handle(), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT);
    queue->submit();
    queue->present();
    queue->waitIdle();

    postRender();
}

void Renderer::resize() {
    uint32_t width = m_surface->currentExtent().width;
    uint32_t height = m_surface->currentExtent().height;

    swapchain->destroy();
    swapchain->create();
    queue->clearSwapchains();
    queue->addSwapchain(swapchain.get());

    imageViews.clear();
    framebuffers.clear();

    depthImage = std::make_unique<Image>(device);
    depthImage->setWidth(width);
    depthImage->setHeight(height);
    depthImage->setFormat(depthFormat);
    depthImage->setUsage(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(device->physicalDevice()->handle(), depthFormat, &props);
    if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        depthImage->setTiling(VK_IMAGE_TILING_LINEAR);
    } else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        depthImage->setTiling(VK_IMAGE_TILING_OPTIMAL);
    } else {
        throw std::runtime_error("VK_FORMAT_D16_UNORM Unsupported");
    }

    depthImage->create();

    depthImageView = std::make_unique<ImageView>(device, depthImage->handle());
    depthImageView->setFormat(depthFormat);
    depthImageView->setAspectMask(VK_IMAGE_ASPECT_DEPTH_BIT);
    depthImageView->create();

    for (const auto& image : swapchain->images()) {
        std::unique_ptr<ImageView> imageView = std::make_unique<ImageView>(device, image);
        imageView->setFormat(m_surface->formats().at(0).format);
        imageView->create();

        std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(device);
        framebuffer->addAttachment(imageView.get());
        framebuffer->addAttachment(depthImageView.get());
        framebuffer->setRenderPass(m_renderPass.get());
        framebuffer->setWidth(width);
        framebuffer->setHeight(height);
        framebuffer->create();

        imageViews.push_back(std::move(imageView));
        framebuffers.push_back(std::move(framebuffer));
    }

    if (!commandBuffers) {
        commandBuffers = std::make_unique<CommandBuffers>(device, m_graphicsCommandPool.get());
        commandBuffers->allocate(swapchain->count());
    }

    markDirty();
}

std::vector<unsigned char> Renderer::readFramebuffer() {
    VkImage srcImage = swapchain->currentImage();

    uint32_t width = m_surface->currentExtent().width;
    uint32_t height = m_surface->currentExtent().height;

    Image image(device);
    image.setWidth(width);
    image.setHeight(height);
    image.setUsage(VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    image.create();
    VkImage dstImage = image.handle();

    CommandBufferOneTime commandBuffer(device, m_graphicsCommandPool.get());
    commandBuffer.setImageLayout(dstImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED,
                     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    commandBuffer.setImageLayout(srcImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                     VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

    bool supportsBlit = device->physicalDevice()->supportBlit(swapchain->imageFormat());
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
    vkGetImageSubresourceLayout(device->handle(), dstImage, &subResource, &subResourceLayout);

    // Map image memory so we can start copying from it
    const unsigned char* data;
    image.memory()->map((void**)&data, VK_WHOLE_SIZE);
    data += subResourceLayout.offset;

    std::vector<unsigned char> output;
    output.resize(width * height * 4);

    uint32_t offset = 0;
    for (uint32_t y = 0; y < height; y++) {
        unsigned int* row = (unsigned int*)data;
        for (uint32_t x = 0; x < width; x++) {
            if (!supportsBlit) {
                // Convert from BGR to RGB
                output[offset++] = *((char*)row + 2);
                output[offset++] = *((char*)row + 1);
                output[offset++] = *((char*)row);
                output[offset++] = *((char*)row + 3);
            } else {
                output[offset++] = *((char*)row + 0);
                output[offset++] = *((char*)row + 1);
                output[offset++] = *((char*)row + 2);
                output[offset++] = *((char*)row + 3);
            }

            row++;
        }

        data += subResourceLayout.rowPitch;
    }

    image.memory()->unmap();

    return std::move(output);
}

void Renderer::buildCommandBuffers() {
    for (int i = 0; i < commandBuffers->count(); i++) {
        CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.reset();
        commandBuffer.begin();
        writeCommandBuffer(&commandBuffer, framebuffers.at(i).get());
        commandBuffer.end();
    }
}

}
