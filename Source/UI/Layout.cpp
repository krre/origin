#include "Layout.h"
#include "Control.h"
#include <algorithm>

namespace Origin {

Layout::Layout(Control* parent) : Control(parent) {

}

Layout::~Layout() {
    clearLayouts();
    clearControls();
}

void Layout::resize(int width, int height) {
    for (const auto& layout : layouts) {
        layout->resize(width, height);
    }
}

void Layout::addControl(Control* control) {
    control->setParent(this);
    controls.push_back(control);
    control->setScreen(screen);
    updateContentPostion();
}

void Layout::removeControl(Control *control) {
    removeChild(control);
    controls.erase(std::remove(controls.begin(), controls.end(), control), controls.end());
    updateContentPostion();
}

void Layout::clearControls() {
    for (const auto control : controls) {
        delete control;
    }

    controls.clear();
}

void Layout::addLayout(Layout* layout) {
    layouts.push_back(layout);
    layout->setScreen(screen);
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
