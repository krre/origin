#include "View2D.h"
#include "Batch2D.h"

namespace Origin {

View2D::View2D() {

}

View2D::~View2D() {

}

void View2D::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {
    batch->controlType = ControlType::VIEW2D;
}

void View2D::writeCommands(Vulkan::CommandBuffer* commandBuffer) {

}

} // Origin
