#include "Screen.h"
#include "Core/Application.h"
#include "UI/Control.h"
#include "UI/Batch2D.h"
#include "UI/View3D.h"
#include "Graphics/RenderContext.h"
#include "Graphics/Render/Renderer.h"

namespace Origin {

Screen::Screen() {

}

Screen::~Screen() {
    if (rootControl != nullptr) {
        delete rootControl;
    }
}

void Screen::hide() {

}

void Screen::pause() {
    isPaused = true;
}

void Screen::resume() {
    isPaused = false;
}

void Screen::show() {

}

void Screen::setRootControl(Control* control) {
    rootControl = control;
}

void Screen::update(float dt) {
    renderViews.clear();
    batches.clear();
    vertices.clear();
    if (rootControl != nullptr) {
        getBatches(rootControl, batches, vertices);
    }
}

void Screen::render() {
    RenderContext::get()->getRenderer()->render(this);
}

void Screen::resize(uint32_t width, uint32_t height) {

}

void Screen::getBatches(Control* control, std::vector<Batch2D>& batches, std::vector<Batch2D::Vertex>& vertices) {
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

void Screen::addView(View* view) {

}

} // Origin
