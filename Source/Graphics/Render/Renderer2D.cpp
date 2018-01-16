#include "Renderer2D.h"
#include "Gui/Control.h"
#include "Gui/View3D.h"

namespace Origin {

Renderer2D::Renderer2D() {

}

Renderer2D::~Renderer2D() {

}

void Renderer2D::render() {

}

void Renderer2D::prepare(Control* control) {
    renderViews.clear();
    batches.clear();
    vertices.clear();
    if (control != nullptr) {
        getBatches(control, batches, vertices);
    }
}

void Renderer2D::getBatches(Control* control, std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) {
    if (!control->getVisible()) return;

    View3D* view3d = dynamic_cast<View3D*>(control);
    if (view3d) {
        renderViews.push_back(view3d);
        return;
    }

    control->prepareBatch(batches, vertices);

    for (auto child : control->getChildren()) {
        if (child->getVisible()) {
            getBatches(child, batches, vertices);
        }
    }
}

} // Origin
