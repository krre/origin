#include "Manager.h"
#include "../../Resource/ShaderResource.h"
#include "../../Resource/ResourceManager.h"

using namespace Vulkan;

Manager::Manager() {

}

Manager::~Manager() {
    renderFinishedSemaphore.reset();
    imageAvailableSemaphore.reset();
    fence.reset();
    commandBuffer.reset();
    commandPool.reset();
    framebuffers.clear();
    graphicsPipeline.reset();
    pipelineLayout.reset();
    renderPass.reset();
    imageViews.clear();
    swapchain.reset();
//    queue.reset();
    surface.reset();
    device.reset();
    physicalDevices.reset();
    debugCallback.reset();
    instance.reset();
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallbackFunc(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
//    std::cerr << "Validation layer: " << msg << std::endl;

    return VK_FALSE;
}

bool Manager::init() {
    instance.reset(new Instance);
    instance->create();

    if (enableValidationLayers) {
        debugCallback.reset(new DebugReportCallback(instance.get(), debugCallbackFunc));
        if (!debugCallback->isValid()) {
            resultDescription = std::string(initError) + debugCallback->getResultDescription();
            return false;
        }
    }

    physicalDevices.reset(new PhysicalDevices(instance.get()));
    device.reset(new Device(physicalDevices.get()));
    if (!device->isValid()) {
        resultDescription = std::string(initError) + device->getResultDescription();
        return false;
    }

    vkGetDeviceQueue(device->getHandle(), 0, 0, &graphicsQueue); // TODO: Set family index and queue index
    vkGetDeviceQueue(device->getHandle(), 0, 0, &presentQueue); // TODO: Set family index and queue index

    return true;
}

bool Manager::createSurface() {
    surface.reset(new Surface(instance.get()));
    if (!surface->isValid()) {
        resultDescription = std::string(initError) + surface->getResultDescription();
        return false;
    }

    surfaceFormat.reset(new SurfaceFormat(physicalDevices.get(), surface.get()));

//    queue.reset(new Queue(device.get()));
//    if (!queue->isValid()) {
//        resultDescription = std::string(initError) + queue->getResultDescription();
//        return false;
//    }

    swapchain.reset(new Swapchain(device.get(), surface.get(), surfaceFormat.get()));
    if (!swapchain->isValid()) {
        resultDescription = std::string(initError) + swapchain->getResultDescription();
        return false;
    }


    for (uint32_t i = 0; i < swapchain->getCount(); i++) {
        std::shared_ptr<ImageView> imageView(new ImageView(device.get(), surfaceFormat.get(), swapchain->getImage(i)));
        if (!imageView->isValid()) {
            resultDescription = std::string(initError) + imageView->getResultDescription();
            return false;
        }
        imageViews.push_back(imageView);
    }

    renderPass.reset(new RenderPass(device.get(), surfaceFormat.get()));
    if (!renderPass->isValid()) {
        resultDescription = std::string(initError) + renderPass->getResultDescription();
        return false;
    }

    pipelineLayout.reset(new PipelineLayout(device.get()));
    if (!pipelineLayout->isValid()) {
        resultDescription = std::string(initError) + pipelineLayout->getResultDescription();
        return false;
    }

    graphicsPipeline.reset(new Pipeline(PipelineType::Graphics, device.get()));
    ShaderResource* shaderResource;

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseVertShader");
    graphicsPipeline->addShaderCode(ShaderType::Vertex, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    shaderResource = ResourceManager::get()->getResource<ShaderResource>("BaseFragShader");
    graphicsPipeline->addShaderCode(ShaderType::Fragment, (size_t)shaderResource->getSize(), (uint32_t*)shaderResource->getData());

    graphicsPipeline->setExtent(swapchain->getExtent());
    graphicsPipeline->setPipelineLayout(pipelineLayout.get());
    graphicsPipeline->setRenderPass(renderPass.get());

    graphicsPipeline->create();

    if (!graphicsPipeline->isValid()) {
        resultDescription = std::string(initError) + graphicsPipeline->getResultDescription();
        return false;
    }

    for (uint32_t i = 0; i < swapchain->getCount(); i++) {
        std::shared_ptr<Framebuffer> framebuffer(new Framebuffer(device.get(), renderPass.get(), imageViews[i].get(), swapchain->getExtent()));
        if (!framebuffer->isValid()) {
            resultDescription = std::string(initError) + framebuffer->getResultDescription();
            return false;
        }
        framebuffers.push_back(framebuffer);
    }

    commandPool.reset(new CommandPool(device.get()));
    if (!commandPool->isValid()) {
        resultDescription = std::string(initError) + commandPool->getResultDescription();
        return false;
    }

    commandBuffer.reset(new CommandBuffer(device.get()));
    commandBuffer->allocate(commandPool.get(), swapchain->getCount());

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

    fence.reset(new Fence(device.get()));
    if (!fence->isValid()) {
        resultDescription = std::string(initError) + fence->getResultDescription();
        return false;
    }

    imageAvailableSemaphore.reset(new Semaphore(device.get()));
    if (!imageAvailableSemaphore->isValid()) {
        resultDescription = std::string(initError) + imageAvailableSemaphore->getResultDescription();
        return false;
    }

    renderFinishedSemaphore.reset(new Semaphore(device.get()));
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
