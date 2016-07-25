#include "Scene2D.h"
#include "../Event/Event.h"
#include <algorithm>

Scene2D::Scene2D() {
    Event::getInstance()->windowResize.connect<Scene2D, &Scene2D::onWindowResize>(this);
}

void Scene2D::draw(float dt) {
    for (auto control : controls) {
        control->draw(dt);
    }
}

void Scene2D::addControl(std::shared_ptr<Control> control) {
    controls.push_back(control);
}

void Scene2D::removeControl(std::shared_ptr<Control> control) {
    controls.erase(std::remove(controls.begin(), controls.end(), control), controls.end());
}

void Scene2D::clearControls() {
    controls.clear();
}

void Scene2D::addLayout(std::shared_ptr<Layout> layout) {
    layouts.push_back(layout);
}

void Scene2D::removeLayout(std::shared_ptr<Layout> layout) {
    layouts.erase(std::remove(layouts.begin(), layouts.end(), layout), layouts.end());
}

void Scene2D::clearLayouts() {
    layouts.clear();
}

void Scene2D::onWindowResize(int width, int height) {

}
