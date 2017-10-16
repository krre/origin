#include "Screen.h"
#include "Scene/Scene.h"

Screen::Screen() {

}

void Screen::hide() {

}

void Screen::pause() {

}

void Screen::resume() {

}

void Screen::show() {

}

void Screen::update(float dt) {
    for (const auto& scene : scenes) {
        scene->update(dt);
    }
}

void Screen::render(float dt) {
    for (const auto& scene : scenes) {
        scene->render(dt);
    }
}

void Screen::resize(uint32_t width, uint32_t height) {
    for (const auto& scene : scenes) {
        scene->resize(width, height);
    }
}

void Screen::pushScene(const std::shared_ptr<Scene>& scene) {
    scenes.push_back(scene);
    currentScene = scene.get();
}

void Screen::popScene() {
    scenes.pop_back();
    currentScene = scenes.size() ? scenes.back().get() : nullptr;
}
