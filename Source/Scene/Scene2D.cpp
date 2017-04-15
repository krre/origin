#include "Scene2D.h"
#include "../UI/Control.h"
#include "../Graphics/Vulkan/Queue/SubmitQueue.h"

Scene2D::Scene2D() {

}

void Scene2D::draw(float dt) {
    batches.clear();
    if (root) {
        root->getBatches(batches);
    }

    queue->submit();
}

void Scene2D::setRoot(std::shared_ptr<Control> root) {
    this->root = root;
}

void Scene2D::onWindowResize(int width, int height) {

}
