#include "Scene.h"
#include "../Event/Event.h"
#include "SceneManager.h"
#include "../Graphics/Vulkan/Manager.h"
#include "../Event/Input.h"

Scene::Scene() {
    device = Vulkan::Manager::get()->getDevice();
    Event::get()->windowResize.connect<Scene, &Scene::onWindowResize>(this);
}

Scene::~Scene() {
    delete commandBuffers;
}

void Scene::init() {
    commandBuffers = new Vulkan::CommandBuffers(device, Vulkan::Manager::get()->getCommandPool());
    commandBuffers->allocate(Vulkan::Manager::get()->getSwapchain()->getImageCount());
}

void Scene::pause() {
    Event::get()->keyPressed.disconnect<Scene, &Scene::onKeyPressed>(this);
}

void Scene::resume() {
    Event::get()->keyPressed.connect<Scene, &Scene::onKeyPressed>(this);
}

void Scene::onKeyPressed(const SDL_KeyboardEvent& event) {
    if (event.keysym.sym == SDLK_ESCAPE) {
        SceneManager::get()->popScene();
        Input::get()->isKeyAccepted = true;
    }
}
