#include "View3D.h"
#include "Batch2D.h"

View3D::View3D() {

}

void View3D::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {
    batch->controlType = ControlType::VIEW3D;
}
