#include "SceneManager.h"
#include "Debug/DebugHUD.h"
#include "Graphics/Vulkan/Instance.h"
#include "Graphics/Vulkan/Swapchain.h"
#include "Graphics/Vulkan/Queue/PresentQueue.h"
#include "Graphics/Vulkan/Semaphore.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "Graphics/Vulkan/Surface.h"

SceneManager::SceneManager() {
    DebugHUD::get()->init();
}

void SceneManager::pushScene(const std::shared_ptr<Scene>& scene) {
    if (!scenes.empty()) {
        scenes.back()->pause();
    }
    scenes.push_back(scene);
    scene->init();
    scene->resume();

    updateSemaphores();
}

void SceneManager::popScene() {
    if (scenes.size() > 1) {
        scenes.back()->pause();
        scenes.pop_back();
        scenes.back()->resume();

        updateSemaphores();
    } else {
        // TODO: Question dialog about exit from game
        PRINT("Exit question dialog")
    }
}

void SceneManager::setScene(const std::shared_ptr<Scene>& scene) {
    for (const auto& scene : scenes) {
        scene->pause();
    }
    scenes.clear();
    pushScene(scene);
}

void SceneManager::update(float dt) {
    scenes.back()->update(dt);

//    if (DebugHUD::get()->getVisible()) {
//        DebugHUD::get()->update(dt);
//    }
}

void SceneManager::draw(float dt) {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->acquireNextImage();

    scenes.back()->draw(dt);

//    if (DebugHUD::get()->getVisible()) {
//        DebugHUD::get()->draw(dt);
//    }

    Vulkan::Instance::get()->getSurface()->getSwapchain()->getPresentQueue()->present();
}

void SceneManager::rebuild() {
    for (const auto& scene : scenes) {
        scene->buildCommandBuffers();
    }

    DebugHUD::get()->buildCommandBuffers();
}

void SceneManager::wait() {
    Vulkan::Instance::get()->getDefaultDevice()->waitIdle();
}

void SceneManager::updateSemaphores() {

}
