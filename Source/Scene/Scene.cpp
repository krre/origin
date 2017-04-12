#include "Scene.h"
#include "../Event/Event.h"
#include "SceneManager.h"
#include "../Graphics/Vulkan/Instance.h"
#include "../Graphics/Vulkan/Surface.h"
#include "../Graphics/Vulkan/Swapchain.h"
#include "../Graphics/Vulkan/Semaphore.h"
#include "../Graphics/Vulkan/Command/CommandBuffers.h"
#include "../Graphics/Vulkan/Command/CommandBuffer.h"
#include "../Graphics/Vulkan/Queue/SubmitQueue.h"
#include "../Graphics/Vulkan/RenderPass.h"
#include "../Graphics/Vulkan/Framebuffer.h"
#include "../Event/Input.h"

Scene::Scene() :
        device(Vulkan::Instance::get()->getDefaultDevice()) {
    Event::get()->windowResize.connect<Scene, &Scene::onWindowResize>(this);

    commandBuffers = std::make_shared<Vulkan::CommandBuffers>(Vulkan::Instance::get()->getCommandPool());
    commandBuffers->allocate(Vulkan::Instance::get()->getSurface()->getSwapchain()->getCount());

    renderFinishedSemaphore = std::make_shared<Vulkan::Semaphore>(device);
    renderFinishedSemaphore->create();

    queue = std::make_shared<Vulkan::SubmitQueue>(Vulkan::Instance::get()->getGraphicsFamily());
    queue->addSignalSemaphore(renderFinishedSemaphore->getHandle());
}

Scene::~Scene() {
    queue->waitIdle();
}

void Scene::init() {
}

void Scene::pause() {
    Event::get()->keyPressed.disconnect<Scene, &Scene::onKeyPressed>(this);
}

void Scene::resume() {
    Event::get()->keyPressed.connect<Scene, &Scene::onKeyPressed>(this);
}

void Scene::buildCommandBuffers() {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->setClearValue({ 0.0, 0.0, 0.0, 0.0 });
    VkRenderPassBeginInfo* renderPassBeginInfo = &Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass()->beginInfo;
    VkExtent2D extent = Vulkan::Instance::get()->getSurface()->getCurrentExtent();
    renderPassBeginInfo->renderArea.extent = extent;

    VkViewport viewport = {};
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.maxDepth = 1.0;

    VkRect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = extent;

    queue->clearCommandBuffers();

    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
        renderPassBeginInfo->framebuffer = Vulkan::Instance::get()->getSurface()->getSwapchain()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.begin();
        commandBuffer.beginRenderPass(renderPassBeginInfo);

        commandBuffer.addViewport(viewport);
        commandBuffer.setViewport(0);

        commandBuffer.addScissor(scissor);
        commandBuffer.setScissor(0);

        writeCommands(&commandBuffer);

        commandBuffer.endRenderPass();
        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}
