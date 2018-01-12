#include "VulkanRenderer.h"
#include "Core/Application.h"
#include "Graphics/Vulkan/Wrapper/Semaphore.h"
#include "Graphics/Vulkan/Wrapper/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/RenderPass.h"
#include "Graphics/Vulkan/Wrapper/Framebuffer.h"
#include "Graphics/Vulkan/VulkanRenderContext.h"
#include "Graphics/Vulkan/VulkanRenderWindow.h"

namespace Origin {

VulkanRenderer::VulkanRenderer() {
    device = vkCtx->getGraphicsDevice();
    window = static_cast<VulkanRenderWindow*>(Application::get()->getWindow());

    commandBufferHandlers = std::make_unique<Vulkan::CommandBuffers>(device, vkCtx->getGraphicsCommandPool());
    commandBufferHandlers->allocate(window->getSwapchain()->getCount());

    for (int i = 0; i < commandBufferHandlers->getCount(); i++) {
        auto commandBuffer = std::make_unique<Vulkan::CommandBuffer>(commandBufferHandlers->at(i));
        commandBuffers.push_back(std::move(commandBuffer));
    }

    submitQueue = std::make_unique<Vulkan::SubmitQueue>(device, vkCtx->getGraphicsFamily());
    submitQueue->create();

    updateCommandBuffers();
}

VulkanRenderer::~VulkanRenderer() {
    submitQueue->waitIdle();
}

void VulkanRenderer::updateCommandBuffers() {
    Vulkan::RenderPass* renderPass = window->getRenderPass();
    const Color& color = window->getColor();
    renderPass->setClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });

    for (int i = 0; i < commandBuffers.size(); i++) {
        renderPass->setFramebuffer(static_cast<VulkanRenderWindow*>(window)->getFrameBuffer(i)->getHandle());

        Vulkan::CommandBuffer* commandBuffer = commandBuffers.at(i).get();
        commandBuffer->reset();
        commandBuffer->begin();

        VkExtent2D extent = { window->getWidth(), window->getHeight() };

        VkViewport viewport = {};
        viewport.width = extent.width;
        viewport.height = extent.height;
        viewport.maxDepth = 1.0;

        VkRect2D scissor = {};
        scissor.offset = { 0, 0 };
        scissor.extent = extent;

        renderPass->setExtent(extent);
        commandBuffer->beginRenderPass(renderPass->getBeginInfo());

        //    commandBuffer->bindPipeline(shaderProgram.getGraphicsPipeline());

        commandBuffer->addViewport(viewport);
        commandBuffer->setViewport(0);

        commandBuffer->addScissor(scissor);
        commandBuffer->setScissor(0);

        //    commandBuffer->addVertexBuffer(vertexBuffer->getHandle());
        //    commandBuffer->bindVertexBuffers();
        //    commandBuffer->bindIndexBuffer(indexBuffer->getHandle(), indexBuffer->getIndexType());

        //    for (int i = 0; i < shaderProgram.getDescriptorSets()->getCount(); i++) {
        //        commandBuffer->addDescriptorSet(shaderProgram.getDescriptorSets()->at(i));
        //    }
        //    commandBuffer->bindDescriptorSets(shaderProgram.getGraphicsPipeline()->getBindPoint(), shaderProgram.getPipelineLayout()->getHandle());
        //    commandBuffer->drawIndexed(MAX_CHAR_COUNT, 1, 0, 0, 0);

        commandBuffer->endRenderPass();

        // TODO: Write commands to commandBuffer

        commandBuffer->end();
    }
}

void VulkanRenderer::renderQueue() {
    submitQueue->clearWaitSemaphores();
    submitQueue->addWaitSemaphore(window->getImageAvailableSemaphore());

    submitQueue->clearCommandBuffers();
    submitQueue->addCommandBuffer(commandBuffers.at(window->getImageIndex()).get(),
                                  window->getImageAvailableSemaphore(), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, window->getRenderFinishedSemaphore());
    submitQueue->submit();
}

} // Origin
