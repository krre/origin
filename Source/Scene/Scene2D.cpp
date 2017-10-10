#include "Scene2D.h"
#include "UI/Control.h"
#include "Graphics/Vulkan/Wrapper/Queue/SubmitQueue.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "UI/Batch2D.h"

Scene2D::Scene2D() {
//    vertexBuffer = std::make_unique<VertexBuffer>(MAX_VERTEX_BUFFER_SIZE);
//    indexBuffer = std::make_unique<IndexBuffer>(MAX_INDEX_COUNT);
}

Scene2D::~Scene2D() {

}

void Scene2D::draw(float dt) {
    batches.clear();
    if (root) {
        root->getBatches(batches, vertexBuffer.get(), indexBuffer.get());
    }

//    queue->submit();
}

void Scene2D::setRootControl(const std::shared_ptr<Control>& root) {
    this->root = root;
    this->root->setSize(size);
}

void Scene2D::onWindowResize(int width, int height) {
    size = Size(width, height);
    if (root) {
        root->setSize(size);
    }
}
