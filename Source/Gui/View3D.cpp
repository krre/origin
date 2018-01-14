#include "View3D.h"
#include "Batch2D.h"

namespace Origin {

View3D::View3D() {

}

View::Dimension View3D::getDimension() const {
    return Dimension::View3D;
}

void View3D::prepareBatch(std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) {

}

} // Origin
