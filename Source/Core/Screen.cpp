#include "Screen.h"
#include "UI/View.h"
#include "Graphics/Render/RenderManager.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"
#include "Graphics/Vulkan/VulkanContext.h"
#include "Graphics/Vulkan/VulkanRenderWindow.h"
#include "Graphics/Vulkan/Wrapper/Semaphore.h"
#include "Graphics/Vulkan/Wrapper/Surface/Swapchain.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffers.h"
#include "Graphics/Vulkan/Wrapper/Command/CommandBuffer.h"
#include "Graphics/Vulkan/Wrapper/RenderPass.h"
#include "Graphics/Vulkan/Wrapper/Framebuffer.h"

Screen::Screen() {
    window = Application::get()->getWindow();
    device = static_cast<VulkanContext*>(VulkanContext::get())->getGraphicsDevice();

    commandBufferHandlers = std::make_unique<Vulkan::CommandBuffers>(device, static_cast<VulkanContext*>(VulkanContext::get())->getGraphicsCommandPool());
    commandBufferHandlers->allocate(static_cast<VulkanRenderWindow*>(window)->getSwapchain()->getCount());

    for (int i = 0; i < commandBufferHandlers->getCount(); i++) {
        auto commandBuffer = std::make_unique<Vulkan::CommandBuffer>(commandBufferHandlers->at(i));
        commandBuffers.push_back(std::move(commandBuffer));
    }
}

Screen::~Screen() {
    if (rootControl != nullptr) {
        delete rootControl;
    }
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

void Screen::setRootControl(Control* control) {
    rootControl = control;
}

void Screen::update(float dt) {
    for (auto* renderView : renderViews) {
        renderView->update(dt);
    }
}

void Screen::resize(uint32_t width, uint32_t height) {
    for (const auto& view : views) {
        view->resize(width, height);
    }
    updateRenderViews();
}

void Screen::pushView(const std::shared_ptr<View>& view) {
//    view->resize(size.width, size.height);
    views.push_back(view);
    currentView = view.get();
//    updateRenderViews();
}

void Screen::popView() {
    views.pop_back();
    currentView = views.size() ? views.back().get() : nullptr;
//    updateRenderViews();
}

void Screen::updateRenderViews() {
    renderViews.clear();
    for (const auto view : views) {
        for (const auto& innerView : view->getInnerViews()) {
            renderViews.push_back(innerView);
        }
    }

    Vulkan::RenderPass* renderPass = static_cast<VulkanRenderWindow*>(window)->getRenderPass();
    const Color& color = static_cast<VulkanRenderWindow*>(window)->getColor();
    renderPass->setClearValue({ color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha() });

    for (auto* renderView : renderViews) {
        for (int i = 0; i < commandBuffers.size(); i++) {
            renderPass->setFramebuffer(static_cast<VulkanRenderWindow*>(window)->getFrameBuffer(i)->getHandle());

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
