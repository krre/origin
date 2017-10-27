#include "Screen.h"
#include "UI/View.h"
#include "Graphics/Render/RenderManager.h"
#include "Core/Application.h"
#include "Graphics/Render/RenderWindow.h"

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
    Application::get()->getWindow()->acquireNextImage();

    for (const auto& renderView : renderViews) {
        RenderManager::get()->renderView(renderView);
    }

    Application::get()->getWindow()->present();
}

void Screen::resize(uint32_t width, uint32_t height) {
    for (const auto& view : views) {
        view->resize(width, height);
    }
}

void Screen::pushView(const std::shared_ptr<View>& view) {
    views.push_back(view);
    currentView = view.get();
    updateRenderViews();
}

void Screen::popView() {
    views.pop_back();
    currentView = views.size() ? views.back().get() : nullptr;
    updateRenderViews();
}

void Screen::updateRenderViews() {
    for (const auto view : views) {
        for (const auto& innerView : view->getInnerViews()) {
            renderViews.push_back(innerView);
        }
    }

    for (auto* renderView : renderViews) {
        PRINT(renderView)
    }
}
