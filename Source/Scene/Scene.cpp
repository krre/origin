#include "Scene.h"
#include "Event/Event.h"
#include "Vulkan/Instance.h"
#include "Vulkan/Surface/Surface.h"
#include "Vulkan/Surface/Swapchain.h"
#include "Vulkan/Semaphore.h"
#include "Vulkan/Command/CommandBuffers.h"
#include "Vulkan/Command/CommandBuffer.h"
#include "Vulkan/Queue.h"
#include "Vulkan/RenderPass.h"
#include "Vulkan/Framebuffer.h"
#include "Event/Input.h"
#include "ECS/Systems/Systems.h"
#include "ECS/EntityManager.h"
#include "ECS/Entity.h"
#include <algorithm>

namespace Origin {

Scene::Scene() {
    Event::get()->windowResize.connect(this, &Scene::onWindowResize);

//    commandBuffers = std::make_shared<Vulkan::CommandBuffers>(Vulkan::Instance::get()->getCommandPool());
//    commandBuffers->allocate(Vulkan::Instance::get()->getSurface()->getSwapchain()->getCount());

//    renderFinishedSemaphore = std::make_shared<Vulkan::Semaphore>();
//    renderFinishedSemaphore->create();

//    queue = std::make_shared<Vulkan::Queue>(Vulkan::Instance::get()->getGraphicsFamily());
//    queue->addSignalSemaphore(renderFinishedSemaphore->getHandle());
}

Scene::~Scene() {
//    queue->waitIdle();
}

void Scene::init() {
}

void Scene::pause() {
    Event::get()->keyPressed.disconnect(keyPressedId);
}

void Scene::resume() {
    keyPressedId = Event::get()->keyPressed.connect(this, &Scene::onKeyPressed);
}

void Scene::update(float dt) {

}

void Scene::render(float dt) {

}

void Scene::resize(uint32_t width, uint32_t height) {

}

void Scene::buildCommandBuffers() {
//    if (renderPass == nullptr) {
//        renderPass = Vulkan::Instance::get()->getSurface()->getSwapchain()->getRenderPass();
//        renderPass->setClearValue({ 0.0, 0.0, 0.0, 0.0 });
//    }

//    queue->clearCommandBuffers();

//    for (size_t i = 0; i < commandBuffers->getCount(); i++) {
//        renderPass->setFramebuffer(Vulkan::Instance::get()->getSurface()->getSwapchain()->getFramebuffer(i)->getHandle());

//        Vulkan::CommandBuffer commandBuffer(commandBuffers->at(i));
//        commandBuffer.begin();

//        writeCommands(&commandBuffer);

//        commandBuffer.end();

//        queue->addCommandBuffer(commandBuffer.getHandle());
//    }
}

//void Scene::setRenderPass(Vulkan::RenderPass* renderPass) {
//    this->renderPass = renderPass;
//}

void Scene::addCamera(const std::shared_ptr<Entity>& camera) {
    cameras.push_back(camera);
}

void Scene::removeCamera(const std::shared_ptr<Entity>& camera) {
    cameras.erase(std::remove(cameras.begin(), cameras.end(), camera), cameras.end());
}

void Scene::clearCameras() {
    cameras.clear();
}

void Scene::setCurrentCamera(const std::shared_ptr<Entity>& currentCamera) {
    this->currentCamera = currentCamera;
    MovementControllerSystem* mcs = static_cast<MovementControllerSystem*>(EntityManager::get()->getSystem(SystemType::MovementController).get());
    mcs->setMoveEntity(currentCamera.get());
    mcs->setRotateEntity(currentCamera.get());

    switchCameras[1] = switchCameras[0];
    switchCameras[0] = currentCamera;
}

void Scene::switchCamera() {
    if (switchCameras[1] != nullptr) {
        setCurrentCamera(switchCameras[1]);
    }
}

void Scene::setPosition(const Pos2& position) {
    this->position = position;
}

void Scene::setSize(const Size& size) {
    this->size = size;
}

void Scene::setRootControl(const std::shared_ptr<Control>& root) {
    this->root = root;
}

} // Origin
