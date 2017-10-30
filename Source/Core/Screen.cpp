#include "Screen.h"
#include "UI/View.h"
#include "Graphics/Render/RenderManager.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Vulkan/Context.h"
#include "Graphics/Vulkan/Semaphore.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Surface/Swapchain.h"
#include "Graphics/Vulkan/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Queue/PresentQueue.h"
#include "Graphics/Vulkan/RenderPass.h"
#include "Graphics/Vulkan/Framebuffer.h"

Screen::Screen(const Size& size) : size(size) {
    window = Application::get()->getWindow();
    device = Vulkan::Context::get()->getGraphicsDevice();

    commandBufferHandlers = std::make_unique<Vulkan::CommandBuffers>(device, Vulkan::Context::get()->getGraphicsCommandPool());
    commandBufferHandlers->allocate(window->getSwapchain()->getCount());

    for (int i = 0; i < commandBufferHandlers->getCount(); i++) {
        auto commandBuffer = std::make_unique<Vulkan::CommandBuffer>(commandBufferHandlers->at(i));
        commandBuffers.push_back(std::move(commandBuffer));
    }

    renderFinishedSemaphore = std::make_unique<Vulkan::Semaphore>(device);
    renderFinishedSemaphore->create();
    window->getPresentQueue()->addWaitSemaphore(renderFinishedSemaphore.get());

    submitQueue = std::make_unique<Vulkan::SubmitQueue>(device, Vulkan::Context::get()->getGraphicsFamily());
    submitQueue->create();
    submitQueue->addWaitSemaphore(window->getImageAvailableSemaphore());
}

Screen::~Screen() {
    submitQueue->waitIdle();
}

void Screen::hide() {

}

void Screen::pause() {
    isPaused = true;
}

void Screen::resume() {
    isPaused = false;
}

void Screen::show() {

}

void Screen::update(float dt) {
    for (auto* renderView : renderViews) {
        renderView->update(dt);
    }
}

void Screen::render() {
    window->acquireNextImage();

    submitQueue->clearCommandBuffers();
    uint32_t imageIndex = window->getSwapchain()->getImageIndex();
    submitQueue->addCommandBuffer(commandBuffers.at(imageIndex).get(), Application::get()->getWindow()->getImageAvailableSemaphore(), VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, renderFinishedSemaphore.get());
    submitQueue->submit();

    window->present();
}

void Screen::resize(uint32_t width, uint32_t height) {
    size.width = width;
    size.height = height;
    for (const auto& view : views) {
        view->resize(width, height);
    }
    updateRenderViews();
}

void Screen::pushView(const std::shared_ptr<View>& view) {
    view->resize(size.width, size.height);
    views.push_back(view);
    currentView = view.get();
    updateRenderViews();
}

void Screen::popView() {
    views.pop_back();
    currentView = views.size() ? views.back().get() : nullptr;
    updateRenderViews();
}

void Screen::updateRenderViews() {
    renderViews.clear();
    for (const auto view : views) {
        for (const auto& innerView : view->getInnerViews()) {
            renderViews.push_back(innerView);
        }
    }

    Vulkan::RenderPass* renderPass = window->getRenderPass();
    renderPass->setClearValue({ 0.0, 1.0, 0.0, 0.0 });

    for (auto* renderView : renderViews) {
        for (int i = 0; i < commandBuffers.size(); i++) {
            renderPass->setFramebuffer(window->getFrameBuffer(i)->getHandle());

            Vulkan::CommandBuffer* commandBuffer = commandBuffers.at(i).get();
            commandBuffer->reset();
            commandBuffer->begin();

            VkExtent2D extent = { renderView->getSize().width, renderView->getSize().height };

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

            renderView->writeCommands(commandBuffer);

            commandBuffer->end();
        }
    }
}
