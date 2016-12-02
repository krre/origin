#include "Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
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
//    delete queue;
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
    instance->create();
    return instance->isValid();
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackFunc(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
//    std::cerr << "Validation layer: " << msg << std::endl;

    return VK_FALSE;
}

bool Manager::init() {
    if (enableValidationLayers) {
        debugCallback = new DebugReportCallback(instance, debugCallbackFunc);
        if (!debugCallback->isValid()) {
            resultDescription = std::string(initError) + debugCallback->getResultDescription();
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
    device->create();
    if (!device->isValid()) {
        resultDescription = std::string(initError) + device->getResultDescription();
        return false;
    }

    vkGetDeviceQueue(device->getHandle(), graphicsFamily, 0, &graphicsQueue);
    vkGetDeviceQueue(device->getHandle(), 0, 0, &presentQueue); // TODO: Set family index and queue index

    return createSurface();
}

bool Manager::createSurface() {
    surface = new Surface(instance, basePhysicalDevice);
    surface->create();
    if (!surface->isValid()) {
        resultDescription = std::string(initError) + surface->getResultDescription();
        return false;
    }

//    queue = new Queue(device);
//    if (!queue->isValid()) {
//        resultDescription = std::string(initError) + queue->getResultDescription();
//        return false;
//    }

    swapchain = new Swapchain(device, surface);
    swapchain->create();
    if (!swapchain->isValid()) {
        resultDescription = std::string(initError) + swapchain->getResultDescription();
        return false;
    }


    for (uint32_t i = 0; i < swapchain->getCount(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device, surface, swapchain->getImage(i)));
        imageView->create();
        if (!imageView->isValid()) {
            resultDescription = std::string(initError) + imageView->getResultDescription();
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass = new RenderPass(device, surface);
    if (!renderPass->isValid()) {
        resultDescription = std::string(initError) + renderPass->getResultDescription();
        return false;
    }

    pipelineLayout = new PipelineLayout(device);
    if (!pipelineLayout->isValid()) {
        resultDescription = std::string(initError) + pipelineLayout->getResultDescription();
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

    graphicsPipeline->create();

    if (!graphicsPipeline->isValid()) {
        resultDescription = std::string(initError) + graphicsPipeline->getResultDescription();
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device, renderPass, imageViews[i].get(), swapchain->getExtent()));
        if (!framebuffer->isValid()) {
            resultDescription = std::string(initError) + framebuffer->getResultDescription();
            return false;
        }
        framebuffers.push_back(framebuffer);
    }

    commandPool = new CommandPool(device, graphicsFamily);
    commandPool->create();
    if (!commandPool->isValid()) {
        resultDescription = std::string(initError) + commandPool->getResultDescription();
        return false;
    }

    commandBuffer = new CommandBuffer(device);
    commandBuffer->allocate(commandPool, swapchain->getCount());

    if (commandBuffer->getResult() != VK_SUCCESS) {
        resultDescription = std::string(initError) + commandBuffer->getResultDescription();
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
    if (!fence->isValid()) {
        resultDescription = std::string(initError) + fence->getResultDescription();
        return false;
    }

    imageAvailableSemaphore = new Semaphore(device);
    if (!imageAvailableSemaphore->isValid()) {
        resultDescription = std::string(initError) + imageAvailableSemaphore->getResultDescription();
        return false;
    }

    renderFinishedSemaphore = new Semaphore(device);
    if (!renderFinishedSemaphore->isValid()) {
        resultDescription = std::string(initError) + renderFinishedSemaphore->getResultDescription();
        return false;
    }

    return true;
}

void Manager::drawFrame() {
    uint32_t imageIndex;
    vkAcquireNextImageKHR(device->getHandle(), swapchain->getHandle(), std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore->getHandle(), VK_NULL_HANDLE, &imageIndex);

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphore->getHandle() };
    VkSemaphore signalSemaphores[] = { renderFinishedSemaphore->getHandle() };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = commandBuffer->getBuffers();
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
        error("Failed to submit draw command buffer!");
        return;
    }

    VkSwapchainKHR swapChains[] = { swapchain->getHandle() };

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(presentQueue, &presentInfo);
}
