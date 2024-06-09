#include "Renderer.h"
#include "api/command/CommandBuffer.h"
#include "api/command/CommandBuffers.h"
#include "api/command/CommandPool.h"
#include "api/device/Device.h"
#include "api/device/PhysicalDevice.h"
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
#include <iostream>

namespace Vulkan {

const VkFormat depthFormat = VK_FORMAT_D16_UNORM;

Renderer::Renderer(void* platformHandle, void* platformWindow) :
        m_platformHandle(platformHandle),
        m_platformWindow(platformWindow) {
    m_instance = std::make_unique<Instance>();
}

Renderer::~Renderer() {
    m_queue->waitIdle();

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

    m_physicalDevices = m_instance->physicalDevices();

    // Default graphics and compute device are same and first in list of physical devices
    PhysicalDevice* graphicsPhysicalDevice = m_physicalDevices[0].get();
    PhysicalDevice* computePhysicalDevice = m_physicalDevices[0].get();

    if (m_physicalDevices.size() > 1) {
        if (m_presetDevice != -1) {
            graphicsPhysicalDevice = m_physicalDevices[m_presetDevice].get();
            computePhysicalDevice = m_physicalDevices[1 - m_presetDevice].get();
        } else {
            // Select by hardware properties
            graphicsPhysicalDevice = findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);

            if (graphicsPhysicalDevice == nullptr) {
                graphicsPhysicalDevice = findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
            }

            computePhysicalDevice = findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);

            if (computePhysicalDevice == nullptr) {
                computePhysicalDevice = findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
            }
        }
    }

    // Create graphics logical device and command pool
    m_graphicsFamily = graphicsPhysicalDevice->findQueueFamily(VK_QUEUE_GRAPHICS_BIT);
    m_graphicsDevice = std::make_unique<Device>(graphicsPhysicalDevice);
    m_graphicsDevice->addQueueCreateInfo(m_graphicsFamily, { 1.0 });
    m_graphicsDevice->create();

    m_graphicsCommandPool = std::make_shared<CommandPool>(m_graphicsDevice.get(), m_graphicsFamily);
    m_graphicsCommandPool->create();

    // Create compute logical device and command pool
    if (graphicsPhysicalDevice != computePhysicalDevice) {
        m_computeFamily = computePhysicalDevice->findQueueFamily(VK_QUEUE_COMPUTE_BIT);
        m_computeDevice = std::make_unique<Device>(computePhysicalDevice);
        m_computeDevice->addQueueCreateInfo(m_computeFamily, { 1.0 });
        m_computeDevice->create();

        m_computeCommandPool = std::make_shared<CommandPool>(m_computeDevice.get(), m_computeFamily);
        m_computeCommandPool->create();
    }

    m_device = m_graphicsDevice.get();

    m_imageAvailableSemaphore = std::make_unique<Semaphore>(m_device);
    m_imageAvailableSemaphore->create();

    m_renderFinishedSemaphore = std::make_unique<Semaphore>(m_device);
    m_renderFinishedSemaphore->create();

    m_queue = std::make_unique<Queue>(m_device, m_graphicsFamily);
    m_queue->create();
    m_queue->addPresentWaitSemaphore(m_renderFinishedSemaphore->handle());

    m_surface = std::make_unique<Surface>(m_instance.get(), m_device->physicalDevice(), m_platformHandle, m_platformWindow);
    m_surface->create();

    m_renderPass = std::make_unique<RenderPass>(m_device);
    m_renderPass->setColorFormat(m_surface->formats().at(0).format);
//    renderPass->setBlendEnable(true);
    m_renderPass->setDepthEnable(true);
    m_renderPass->setDepthFormat(depthFormat);
    m_renderPass->create();

    m_swapchain = std::make_unique<Swapchain>(m_device, m_surface.get());

    resize();
    init();
}

void Renderer::render() {
    preRender();

    VkResult result = m_swapchain->acquireNextImage(m_imageAvailableSemaphore.get());
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        resize();
    }

    if (m_dirty) {
        buildCommandBuffers();
        m_dirty = false;
    }

    m_queue->clearCommandBuffers();
    m_queue->addCommandBuffer(m_commandBuffers->at(m_swapchain->imageIndex()),
                            m_renderFinishedSemaphore->handle(),
                            m_imageAvailableSemaphore->handle(), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT);
    m_queue->submit();
    m_queue->present();
    m_queue->waitIdle();

    postRender();
}

void Renderer::resize() {
    uint32_t width = m_surface->currentExtent().width;
    uint32_t height = m_surface->currentExtent().height;

    m_swapchain->destroy();
    m_swapchain->create();
    m_queue->clearSwapchains();
    m_queue->addSwapchain(m_swapchain.get());

    m_imageViews.clear();
    m_framebuffers.clear();

    m_depthImage = std::make_unique<Image>(m_device);
    m_depthImage->setWidth(width);
    m_depthImage->setHeight(height);
    m_depthImage->setFormat(depthFormat);
    m_depthImage->setUsage(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(m_device->physicalDevice()->handle(), depthFormat, &props);
    if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        m_depthImage->setTiling(VK_IMAGE_TILING_LINEAR);
    } else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
        m_depthImage->setTiling(VK_IMAGE_TILING_OPTIMAL);
    } else {
        throw std::runtime_error("VK_FORMAT_D16_UNORM Unsupported");
    }

    m_depthImage->create();

    m_depthImageView = std::make_unique<ImageView>(m_device, m_depthImage->handle());
    m_depthImageView->setFormat(depthFormat);
    m_depthImageView->setAspectMask(VK_IMAGE_ASPECT_DEPTH_BIT);
    m_depthImageView->create();

    for (const auto& image : m_swapchain->images()) {
        std::unique_ptr<ImageView> imageView = std::make_unique<ImageView>(m_device, image);
        imageView->setFormat(m_surface->formats().at(0).format);
        imageView->create();

        std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(m_device);
        framebuffer->addAttachment(imageView.get());
        framebuffer->addAttachment(m_depthImageView.get());
        framebuffer->setRenderPass(m_renderPass.get());
        framebuffer->setWidth(width);
        framebuffer->setHeight(height);
        framebuffer->create();

        m_imageViews.push_back(std::move(imageView));
        m_framebuffers.push_back(std::move(framebuffer));
    }

    if (!m_commandBuffers) {
        m_commandBuffers = std::make_unique<CommandBuffers>(m_device, m_graphicsCommandPool.get());
        m_commandBuffers->allocate(m_swapchain->count());
    }

    markDirty();
}

std::vector<unsigned char> Renderer::readFramebuffer() {
    VkImage srcImage = m_swapchain->currentImage();

    uint32_t width = m_surface->currentExtent().width;
    uint32_t height = m_surface->currentExtent().height;

    Image image(m_device);
    image.setWidth(width);
    image.setHeight(height);
    image.setUsage(VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    image.create();
    VkImage dstImage = image.handle();

    CommandBufferOneTime commandBuffer(m_device, m_graphicsCommandPool.get());
    commandBuffer.setImageLayout(dstImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED,
                     VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    commandBuffer.setImageLayout(srcImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                     VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

    bool supportsBlit = m_device->physicalDevice()->supportBlit(m_swapchain->imageFormat());
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
    vkGetImageSubresourceLayout(m_device->handle(), dstImage, &subResource, &subResourceLayout);

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
    for (int i = 0; i < m_commandBuffers->count(); i++) {
        CommandBuffer commandBuffer(m_commandBuffers->at(i));
        commandBuffer.reset();
        commandBuffer.begin();
        writeCommandBuffer(&commandBuffer, m_framebuffers.at(i).get());
        commandBuffer.end();
    }
}

PhysicalDevice* Renderer::findDevice(VkPhysicalDeviceType type) const {
    for (const auto& device : m_physicalDevices) {
        if (device->properties().deviceType == type) {
            return device.get();
        }
    }

    return nullptr;
}

}
