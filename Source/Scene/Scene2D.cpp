#include "Scene2D.h"
#include "../UI/Layout.h"
#include "../Graphics/Vulkan/Queue/SubmitQueue.h"
#include <algorithm>

Scene2D::Scene2D() {

}

void Scene2D::draw(float dt) {
    queue->submit();
}

void Scene2D::setRoot(std::shared_ptr<Control> root) {
    this->root = root;
}

void Scene2D::onWindowResize(int width, int height) {

}
