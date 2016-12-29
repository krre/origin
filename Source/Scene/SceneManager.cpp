#include "SceneManager.h"

SceneManager::SceneManager() {

}

void SceneManager::pushScene(std::shared_ptr<Scene> scene) {
    if (scenes.size()) {
        scenes.back()->pause();
    }
    scenes.push_back(scene);
    scene->init();
    scene->resume();
}

void SceneManager::popScene() {
    scenes.pop_back();
    scenes.back()->resume();
}

void SceneManager::setScene(std::shared_ptr<Scene> scene) {
    scenes.clear();
    pushScene(scene);
    scene->resume();
}

void SceneManager::update(float dt) {
    if (scenes.size() > 1) {
        for (auto scene : scenes) {
            scene->update(dt);
        }
    } else {
        scenes.back()->update(dt);
    }
}

void SceneManager::draw(float dt) {
    for (auto scene : scenes) {
        scene->draw(dt);
    }
}
