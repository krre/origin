#include "Scene.h"
#include "../Event/Event.h"
#include "SceneManager.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Event/Input.h"

Scene::Scene() :
        device(Vulkan::Manager::get()->getDevice()),
        commandBuffers(device, Vulkan::Manager::get()->getCommandPool()) {
    Event::get()->windowResize.connect<Scene, &Scene::onWindowResize>(this);
}

Scene::~Scene() {
}

void Scene::init() {
    commandBuffers.allocate(Vulkan::Manager::get()->getSwapchain()->getImageCount());
}

void Scene::pause() {
    Event::get()->keyPressed.disconnect<Scene, &Scene::onKeyPressed>(this);
}

void Scene::resume() {
    Event::get()->keyPressed.connect<Scene, &Scene::onKeyPressed>(this);
}
