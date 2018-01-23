#include "Scene2D.h"
#include "Gui/Control.h"
#include "Vulkan/Queue.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Gui/Batch2D.h"

namespace Origin {

Scene2D::Scene2D() {
//    vertexBuffer = std::make_unique<VertexBuffer>(MAX_VERTEX_BUFFER_SIZE);
//    indexBuffer = std::make_unique<IndexBuffer>(MAX_INDEX_COUNT);
}

Scene2D::~Scene2D() {

}

void Scene2D::render(float dt) {
    batches.clear();
//    if (root) {
//        root->getBatches(batches, vertexBuffer.get(), indexBuffer.get());
//    }

//    queue->submit();
}

void Scene2D::onWindowResize(int width, int height) {
    size = Size(width, height);
//    if (root) {
//        root->setSize(size);
//    }
}

} // Origin
