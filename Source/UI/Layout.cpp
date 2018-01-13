#include "Layout.h"
#include <algorithm>

namespace Origin {

Layout::Layout() {

}

void Layout::resize(int width, int height) {
    for (const auto& layout : layouts) {
        layout->resize(width, height);
    }
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

void Layout::addLayout(const std::shared_ptr<Layout>& layout) {
    layouts.push_back(layout);
    layout->setParent(this);
    updateContentPostion();
}

void Layout::removeLayout(const std::shared_ptr<Layout>& layout) {
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

void Layout::prepareBatch(std::vector<Batch2D>& batches, std::vector<float>& vertices) {

}

} // Origin
