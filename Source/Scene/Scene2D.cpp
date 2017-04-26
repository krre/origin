#include "Scene2D.h"
#include "UI/Control.h"
#include "Graphics/Vulkan/Queue/SubmitQueue.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "UI/Batch2D.h"

Scene2D::Scene2D() {
    vertexBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer(MAX_VERTEX_BUFFER_SIZE));
    indexBuffer = std::unique_ptr<IndexBuffer>(new IndexBuffer(MAX_INDEX_COUNT));
}

Scene2D::~Scene2D() {

}

void Scene2D::draw(float dt) {
    batches.clear();
    if (root) {
        root->getBatches(batches, vertexBuffer.get(), indexBuffer.get());
    }

    queue->submit();
}

void Scene2D::setRoot(std::shared_ptr<Control> root) {
    this->root = root;
}

void Scene2D::onWindowResize(int width, int height) {

}
