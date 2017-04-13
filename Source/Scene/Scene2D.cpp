#include "Scene2D.h"
#include "../UI/Layout.h"
#include <algorithm>

Scene2D::Scene2D() {

}

void Scene2D::draw(float dt) {

}

void Scene2D::setRoot(std::shared_ptr<Control> root) {
    this->root = root;
}

void Scene2D::onWindowResize(int width, int height) {

}
