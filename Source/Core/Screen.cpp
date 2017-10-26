#include "Screen.h"
#include "UI/View.h"
#include "Graphics/Render/RenderManager.h"

Screen::Screen() {

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

void Screen::update(float dt) {
    if (!isPaused) {
        for (const auto& view : views) {
            view->update(dt);
        }
    }
}

void Screen::render() {
    for (const auto& view : views) {
        RenderManager::get()->renderView(view.get());
    }
}

void Screen::resize(uint32_t width, uint32_t height) {
    for (const auto& view : views) {
        view->resize(width, height);
    }
}

void Screen::pushView(const std::shared_ptr<View>& view) {
    views.push_back(view);
    currentView = view.get();
}

void Screen::popView() {
    views.pop_back();
    currentView = views.size() ? views.back().get() : nullptr;
}
