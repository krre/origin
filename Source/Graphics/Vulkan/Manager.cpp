#include "Manager.h"
#include "Image.h"
#include "../../Core/App.h"
#include "Command/CommandBuffer.h"
#include <glm/glm.hpp>

using namespace Vulkan;

Manager::Manager() {

}

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
        "VK_LAYER_LUNARG_image",
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
    if (mainPhysicalDevice == VK_NULL_HANDLE) {
        mainPhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsFamily = physicalDevices->findQueue(mainPhysicalDevice, VK_QUEUE_GRAPHICS_BIT);

    device = new Device(mainPhysicalDevice, graphicsFamily);
    if (device->create() != VK_SUCCESS) {
        return false;
    }

    commandPool = new CommandPool(device, graphicsFamily);
    if (commandPool->create() != VK_SUCCESS) {
        return false;
    }
    commandPool->reset();

    surface = new Surface(instance, mainPhysicalDevice);
    if (surface->create() != VK_SUCCESS) {
        return false;
    }

    swapchain = new Swapchain(device, surface);
    if (swapchain->create() != VK_SUCCESS) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device, surface, swapchain->getImage(i)));
        if (imageView->create() != VK_SUCCESS) {
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass = new RenderPass(device, surface);
    if (renderPass->create() != VK_SUCCESS) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device, renderPass, imageViews[i].get(), swapchain->getExtent()));
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

    graphicsQueue = new SubmitQueue(device, graphicsFamily, 0);
    graphicsQueue->setSignalSemaphores({ renderFinishedSemaphore->getHandle() });
    graphicsQueue->setWaitSemaphores({ imageAvailableSemaphore->getHandle() });
    graphicsQueue->setWaitDstStageMask({ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT });

    presentQueue = new PresentQueue(device, 0, 0); // TODO: Set family index and queue index
    presentQueue->setWaitSemaphores({ renderFinishedSemaphore->getHandle() });
    presentQueue->setSwapchains({ swapchain->getHandle() });
    presentQueue->setImageIndices(&swapchainImageIndex);

    return true;
}

void Manager::setCommandBuffers(uint32_t count, const VkCommandBuffer* data) {
    graphicsQueue->setCommandBuffers(count, data);
}

void Manager::setCommandBuffers(const CommandBuffers* commandBuffers) {
    graphicsQueue->setCommandBuffers(commandBuffers->getCount(), commandBuffers->getData());
}

void Manager::render() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, &swapchainImageIndex);
    graphicsQueue->submit();
    presentQueue->present();
}

void Manager::saveScreenshot(const std::string& filePath) {
    print(filePath)

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


    commandBuffer.end();
}
