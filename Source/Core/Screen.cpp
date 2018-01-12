#include "Screen.h"
#include "UI/View.h"
#include "Core/Application.h"

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
    for (auto* renderView : renderViews) {
        renderView->update(dt);
    }
}

void Screen::resize(uint32_t width, uint32_t height) {
    for (const auto& view : views) {
        view->resize(width, height);
    }
}

void Screen::pushView(const std::shared_ptr<View>& view) {
//    view->resize(size.width, size.height);
    views.push_back(view);
    currentView = view.get();
}

void Screen::popView() {
    views.pop_back();
    currentView = views.size() ? views.back().get() : nullptr;
}

} // Origin
