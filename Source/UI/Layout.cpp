#include "Layout.h"
#include <algorithm>

Layout::Layout() {

}

void Layout::resize(int width, int height) {
    for (const auto& layout : layouts) {
        layout->resize(width, height);
    }
}

void Layout::draw(float dt) {
    for (const auto& layout : layouts) {
        layout->draw(dt);
    }

    for (const auto& control : controls) {
        control->draw(dt);
    }
}

void Layout::update(float dt) {

}

void Layout::addControl(Control* control) {
    controls.push_back(control);
    updateContentPostion();
}

void Layout::removeControl(Control *control) {
    controls.erase(std::remove(controls.begin(), controls.end(), control), controls.end());
    updateContentPostion();
}

void Layout::clearControls() {
    controls.clear();
}

void Layout::addLayout(std::shared_ptr<Layout> layout) {
    layouts.push_back(layout);
    layout->setParent(this);
    updateContentPostion();
}

void Layout::removeLayout(std::shared_ptr<Layout> layout) {
    layouts.erase(std::remove(layouts.begin(), layouts.end(), layout), layouts.end());
    layout->setParent(nullptr);
    updateContentPostion();
}

void Layout::clearLayouts() {
    for (const auto& layout : layouts) {
        layout->setParent(nullptr);
    }
    layouts.clear();
}

void Layout::setSpacing(int spacing) {
    this->spacing = spacing;
}

void Layout::setParent(Control* parent) {
    this->parent = parent;
}

void Layout::update() {
    updateContentPostion();
}

void Layout::prepareBatch(Batch2D* batch, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {

}

