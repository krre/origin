#include "Scene.h"
#include "../Event/Event.h"
#include "SceneManager.h"
#include "../Graphics/Vulkan/Instance.h"
#include "../Graphics/Vulkan/Surface.h"
#include "../Graphics/Vulkan/Swapchain.h"
#include "../Event/Input.h"

Scene::Scene() :
        device(Vulkan::Instance::get()->getDefaultDevice()),
        commandBuffers(Vulkan::Instance::get()->getCommandPool()) {
    Event::get()->windowResize.connect<Scene, &Scene::onWindowResize>(this);

    commandBuffers.allocate(Vulkan::Instance::get()->getSurface()->getSwapchain()->getCount());

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
