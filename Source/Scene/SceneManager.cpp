#include "SceneManager.h"
#include "Core/App.h"
#include "Graphics/Render/RenderWindow.h"
#include "Debug/DebugHUD.h"
#include "Graphics/Render/RenderManager.h"

SceneManager::SceneManager() {
    DebugHUD::get()->init();
//    renderManager = std::make_unique<RenderManager>();
}

void SceneManager::pushScene(const std::shared_ptr<Scene>& scene) {
    if (!scenes.empty()) {
        scenes.back()->pause();
    }
    scenes.push_back(scene);
    scene->init();
    scene->resume();
}

void SceneManager::popScene() {
    if (scenes.size() > 1) {
        scenes.back()->pause();
        scenes.pop_back();
        scenes.back()->resume();
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
    scenes.back()->draw(dt);

//    if (DebugHUD::get()->getVisible()) {
//        DebugHUD::get()->draw(dt);
//    }

    App::get()->getWindow()->swapBuffers();
}

void SceneManager::rebuild() {
    for (const auto& scene : scenes) {
        scene->buildCommandBuffers();
    }

    DebugHUD::get()->buildCommandBuffers();
}
