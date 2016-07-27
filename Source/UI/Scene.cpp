#include "Scene.h"
#include "../Event/Event.h"
#include <algorithm>

Scene::Scene() {
    Event::getInstance()->windowResize.connect<Scene, &Scene::onWindowResize>(this);
}

void Scene::draw(float dt) {
    if (layout != nullptr) {
        layout->draw(dt);
    }

    for (auto control : controls) {
        control->draw(dt);
    }
}

void Scene::addControl(std::shared_ptr<Control> control) {
    controls.push_back(control);
}

void Scene::removeControl(std::shared_ptr<Control> control) {
    controls.erase(std::remove(controls.begin(), controls.end(), control), controls.end());
}

void Scene::clearControls() {
    controls.clear();
}

void Scene::setLayout(std::shared_ptr<Layout> layout) {
    this->layout = layout;
    this->layout->setParent(this);
}

void Scene::onWindowResize(int width, int height) {
    if (layout != nullptr) {
        layout->resize(width, height);
    }
}
