#include "Layout.h"
#include "Control.h"
#include <algorithm>

namespace Origin {

Layout::Layout(Control* parent) : Control(parent) {

}

Layout::~Layout() {
    clearLayouts();
}

void Layout::resize(int width, int height) {
    for (const auto& layout : layouts) {
        layout->resize(width, height);
    }
}

void Layout::notifyAddChild(Object* child) {
    updateContentPostion();
}

void Layout::notifyRemoveChild(Object* child) {
    updateContentPostion();
}

void Layout::addLayout(Layout* layout) {
    layouts.push_back(layout);
    updateContentPostion();
}

void Layout::removeLayout(Layout* layout) {
    layouts.erase(std::remove(layouts.begin(), layouts.end(), layout), layouts.end());
    updateContentPostion();
}

void Layout::clearLayouts() {
    for (const auto& layout : layouts) {
        delete layout;
    }
    layouts.clear();
}

void Layout::setSpacing(int spacing) {
    this->spacing = spacing;
}

} // Origin
