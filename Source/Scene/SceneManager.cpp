#include "SceneManager.h"

SceneManager::SceneManager() {

}

void SceneManager::pushScene(std::shared_ptr<Scene> scene) {
    if (scenes.size()) {
        scenes.back()->pause();
        if (scene->getIsFullScreen()) {
            scenes.back()->setVisible(false);
        }
    }
    scenes.push_back(scene);
    scene->init();
    scene->create();
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
        print("Exit question dialog")
    }
}

void SceneManager::setScene(std::shared_ptr<Scene> scene) {
    for (auto scene : scenes) {
        scene->pause();
        scene->cleanup();
    }
    scenes.clear();
    pushScene(scene);
}

void SceneManager::update(float dt) {
    for (auto scene : scenes) {
        if (scene->getVisible()) {
            scene->update(dt);
        }
    }
}

void SceneManager::draw(float dt) {
    for (auto scene : scenes) {
        if (scene->getVisible()) {
            scene->draw(dt);
        }
    }
}
