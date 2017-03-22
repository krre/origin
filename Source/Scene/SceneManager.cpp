#include "SceneManager.h"
#include "../Debug/DebugHUD.h"
#include "../Graphics/Vulkan/Manager.h"

SceneManager::SceneManager() {
    DebugHUD::get()->init();
}

void SceneManager::pushScene(std::shared_ptr<Scene> scene) {
    if (!scenes.empty()) {
        scenes.back()->pause();
        if (scene->getIsFullScreen()) {
            scenes.back()->setVisible(false);
        }
    }
    scenes.push_back(scene);
    scene->init();
    scene->resume();
}

void SceneManager::popScene() {
    if (scenes.size() > 1) {
        scenes.back()->pause();
        scenes.back()->cleanup();
        scenes.pop_back();
        scenes.back()->resume();
        scenes.back()->setVisible(true);
    } else {
        // TODO: Question dialog about exit from game
        PRINT("Exit question dialog")
    }
}

void SceneManager::setScene(std::shared_ptr<Scene> scene) {
    for (auto& scene : scenes) {
        scene->pause();
        scene->cleanup();
    }
    scenes.clear();
    pushScene(scene);
}

void SceneManager::update(float dt) {
    for (auto& scene : scenes) {
        if (scene->getVisible()) {
            scene->update(dt);
        }
    }

    if (DebugHUD::get()->getVisible()) {
        DebugHUD::get()->update(dt);
    }
}

void SceneManager::draw(float dt) {
    Vulkan::Manager::get()->renderBegin();

    for (auto& scene : scenes) {
        if (scene->getVisible()) {
            scene->draw(dt);
        }
    }

    if (DebugHUD::get()->getVisible()) {
        DebugHUD::get()->draw(dt);
    }

    Vulkan::Manager::get()->renderEnd();
}
