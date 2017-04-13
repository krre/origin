#include "Scene2D.h"
#include "../UI/Layout.h"
#include <algorithm>

Scene2D::Scene2D() {

}

void Scene2D::draw(float dt) {
    if (layout != nullptr) {
        layout->draw(dt);
    }

    for (auto& control : controls) {
        control->draw(dt);
    }
}

void Scene2D::setLayout(std::shared_ptr<Layout> layout) {
    this->layout = layout;
    //    this->layout->setParent(this);
}

void Scene2D::setRoot(std::shared_ptr<Control> root) {
    this->root = root;
}

void Scene2D::onWindowResize(int width, int height) {
    if (layout != nullptr) {
        layout->resize(width, height);
    }
}
