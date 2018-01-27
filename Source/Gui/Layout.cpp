#include "Layout.h"
#include "Control.h"
#include <algorithm>

namespace Origin {

Layout::Layout() {

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

void Layout::setScreen(Screen* screen) {
    this->screen = screen;

    for (const auto control : controls) {
        control->setScreen(screen);
    }
}

void Layout::addControl(Control* control) {
    controls.push_back(control);
    control->setScreen(screen);
    updateContentPostion();
}

void Layout::removeControl(Control *control) {
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

void Layout::update(float dt) {
    for (const auto& layout : layouts) {
        layout->update(dt);
    }

    for (const auto control : controls) {
        control->update(dt);
    }

    updateContentPostion();
}

void Layout::draw() {
    for (const auto& layout : layouts) {
        layout->draw();
    }

    for (const auto control : controls) {
        control->draw();
    }
}

} // Origin
