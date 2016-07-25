#include "Scene2D.h"
#include <algorithm>

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
