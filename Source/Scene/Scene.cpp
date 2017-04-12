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

Scene::Scene() {
    Event::get()->windowResize.connect<Scene, &Scene::onWindowResize>(this);

    commandBuffers = std::make_shared<Vulkan::CommandBuffers>(Vulkan::Instance::get()->getCommandPool());
    commandBuffers->allocate(Vulkan::Instance::get()->getSurface()->getSwapchain()->getCount());

    renderFinishedSemaphore = std::make_shared<Vulkan::Semaphore>();
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
    if (renderPass == nullptr) {
        renderPass = Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass();
        renderPass->setClearValue({ 0.0, 0.0, 0.0, 0.0 });
    }

    queue->clearCommandBuffers();

    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
        renderPass->beginInfo.framebuffer = Vulkan::Instance::get()->getSurface()->getSwapchain()->getFramebuffer(i)->getHandle();

        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
        commandBuffer.begin();

        writeCommands(&commandBuffer);

        commandBuffer.end();

        queue->addCommandBuffer(commandBuffer.getHandle());
    }
}

void Scene::setRenderPass(Vulkan::RenderPass* renderPass) {
    this->renderPass = renderPass;
}
