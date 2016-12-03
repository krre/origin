#include "Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
    delete presentQueue;
    delete graphicsQueue;
    delete renderFinishedSemaphore;
    delete imageAvailableSemaphore;
    delete fence;
    delete commandBuffer;
    delete commandPool;
    framebuffers.clear();
    delete graphicsPipeline;
    delete pipelineLayout;
    delete renderPass;
    imageViews.clear();
    delete swapchain;
    delete surface;
    delete device;
    delete physicalDevices;
    delete debugCallback;
    delete instance;
}

bool Manager::createInstance() {
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
    return instance->create();
}

bool Manager::init() {
    if (enableValidationLayers) {
        debugCallback = new DebugReportCallback(instance);
        if (!debugCallback->create()) {
            return false;
        }
    }

    physicalDevices = new PhysicalDevices(instance);
    basePhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (basePhysicalDevice == VK_NULL_HANDLE) {
        basePhysicalDevice = physicalDevices->findDevice(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    }

    graphicsFamily = physicalDevices->findQueue(basePhysicalDevice, VK_QUEUE_GRAPHICS_BIT);

    device = new Device(basePhysicalDevice, graphicsFamily);
    if (!device->create()) {
        return false;
    }

    graphicsQueue = new Queue(device, graphicsFamily, 0);
    presentQueue = new Queue(device, 0, 0); // TODO: Set family index and queue index

    surface = new Surface(instance, basePhysicalDevice);
    if (!surface->create()) {
        return false;
    }

    swapchain = new Swapchain(device, surface);
    if (!swapchain->create()) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device, surface, swapchain->getImage(i)));
        if (!imageView->create()) {
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass = new RenderPass(device, surface);
    if (!renderPass->create()) {
        return false;
    }

    pipelineLayout = new PipelineLayout(device);
    if (!pipelineLayout->create()) {
        return false;
    }

    graphicsPipeline = new Pipeline(PipelineType::Graphics, device);
    ShaderResource* shaderResource;

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseVertShader");
    graphicsPipeline->addShaderCode(ShaderType::Vertex, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseFragShader");
    graphicsPipeline->addShaderCode(ShaderType::Fragment, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    graphicsPipeline->setExtent(swapchain->getExtent());
    graphicsPipeline->setPipelineLayout(pipelineLayout);
    graphicsPipeline->setRenderPass(renderPass);

    if (!graphicsPipeline->create()) {
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getImageCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device, renderPass, imageViews[i].get(), swapchain->getExtent()));
        if (!framebuffer->create()) {
            return false;
        }
        framebuffers.push_back(framebuffer);
    }

    commandPool = new CommandPool(device, graphicsFamily);
    if (!commandPool->create()) {
        return false;
    }
    commandPool->reset();

    commandBuffer = new CommandBuffer(device);
    if (!commandBuffer->allocate(commandPool, swapchain->getImageCount())) {
        return false;
    }

    for (size_t i = 0; i < commandBuffer->getCount(); i++) {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        VkCommandBuffer buffer = commandBuffer->getBuffer(i);

        vkBeginCommandBuffer(buffer, &beginInfo);

        VkClearValue clearColor = { 0.77, 0.83, 0.83, 1.0 };

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass->getHandle();
        renderPassInfo.framebuffer = framebuffers[i]->getHandle();
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapchain->getExtent();
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->getHandle());
        vkCmdDraw(buffer, 3, 1, 0, 0);

        vkCmdEndRenderPass(buffer);

        VkResult result = vkEndCommandBuffer(buffer);
        if (result != VK_SUCCESS) {
            error("Error vkEndCommandBuffer"); // TODO: Replace by common error handler
        }
    }

    fence = new Fence(device);
    if (!fence->create()) {
        return false;
    }

    imageAvailableSemaphore = new Semaphore(device);
    if (!imageAvailableSemaphore->create()) {
        return false;
    }

    graphicsQueue->setWaitSemaphores({ imageAvailableSemaphore->getHandle() }, true);

    renderFinishedSemaphore = new Semaphore(device);
    if (!renderFinishedSemaphore->create()) {
        return false;
    }

    graphicsQueue->setSignalSemaphores({ renderFinishedSemaphore->getHandle() });
    graphicsQueue->setWaitDstStageMask({ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT });
    graphicsQueue->setCommandBuffersCount(commandBuffer->getCount());
    graphicsQueue->setCommandBuffersData(commandBuffer->getBuffers());

    presentQueue->setWaitSemaphores({ renderFinishedSemaphore->getHandle() }, false);
    presentQueue->setSwapchains({ swapchain->getHandle() });
    presentQueue->setImageIndices(&swapchainImageIndex);

    return true;
}

void Manager::drawFrame() {
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, &swapchainImageIndex);
    graphicsQueue->submit();
    presentQueue->present();
}
