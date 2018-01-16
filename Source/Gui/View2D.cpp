#include "View2D.h"
#include "Batch2D.h"

namespace Origin {

View2D::View2D() {

}

View2D::~View2D() {

}

View::Dimension View2D::getDimension() const {
    return Dimension::View2D;
}

void View2D::prepareBatch(std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) {

}

} // Origin
