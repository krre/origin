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
        scenes.back()->setVisible(true);

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
    for (const auto& scene : scenes) {
        if (scene->getVisible()) {
            scene->update(dt);
        }
    }

    if (DebugHUD::get()->getVisible()) {
        DebugHUD::get()->update(dt);
    }
}

void SceneManager::draw(float dt) {
    Vulkan::Instance::get()->getSurface()->getSwapchain()->acquireNextImage();

    for (const auto& scene : scenes) {
        if (scene->getVisible()) {
            scene->draw(dt);
        }
    }

    if (DebugHUD::get()->getVisible()) {
        DebugHUD::get()->draw(dt);
    }

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
    std::vector<Scene*> visibleScenes;
    for (const auto& scene : scenes) {
        if (scene->getVisible()) {
            visibleScenes.push_back(scene.get());
        }
    }

    if (DebugHUD::get()->getVisible()) {
        visibleScenes.push_back(DebugHUD::get());
    }

    Scene* firstScene = visibleScenes.front();
    firstScene->getQueue()->setWaitSemaphore(Vulkan::Instance::get()->getSurface()->getSwapchain()->getImageAvailableSemaphore()->getHandle(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

    Scene* lastScene = visibleScenes.back();
    Vulkan::Instance::get()->getSurface()->getSwapchain()->getPresentQueue()->setWaitSemaphore(lastScene->getRenderFinishedSemaphore()->getHandle());

    for (int i = 0; i < visibleScenes.size(); i++) {
        if (i < visibleScenes.size() - 1) {
            visibleScenes.at(i + 1)->getQueue()->setWaitSemaphore(visibleScenes.at(i)->getRenderFinishedSemaphore()->getHandle(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
        }
    }
}
