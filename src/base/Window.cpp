#include "Window.h"
#include "base/Game.h"
#include "base/Settings.h"
#include "base/Constants.h"
#include "base/Defines.h"
#include "screen/Screen.h"
#include "base/Game.h"
#include "event/Event.h"
#include "event/Input.h"
#include "core/Defines.h"
#include "ui/Overlay.h"
#include "debug/Console.h"
#include "graphics/render/RenderManager.h"
#include "graphics/render/SceneRenderer.h"
#include "graphics/render/UIRenderer.h"
#include <lodepng/lodepng.h>
#include <SDL.h>

Window::Window(Object* parent) : SingleObject(parent) {
    json settingsWidth = Settings::getStorage()["width"];
    json settingsHeigth = Settings::getStorage()["height"];

    if (!settingsWidth.is_null()) {
        width = settingsWidth.get<int>();
    }

    if (!settingsHeigth.is_null()) {
        height = settingsHeigth.get<int>();
    }

    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;

// On some Ubuntu OS 'Y' position is shifted on window creation, so do not use position settings
#if !defined(OS_LINUX)
    json settingsX = Settings::getStorage()["x"];
    json settingsY = Settings::getStorage()["y"];

    if (!settingsX.is_null() && !settingsY.is_null()) {
        x = settingsX.get<int>();
        y = settingsY.get<int>();
    }
#endif

    handle = SDL_CreateWindow(Constants::App::NAME, x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }

    Event::get()->windowResize.connect(this, &Window::onResize);
    Event::get()->keyPressed.connect(this, &Window::onKeyPressed);
}

Window::~Window() {

}

void Window::pushScreen(const std::shared_ptr<Screen>& screen) {
    if (!screens.empty()) {
        screens.back()->pause();
    }
    screens.push_back(screen);
    screen->resize(width, height);
    screen->resume();
}

void Window::popScreen() {
    addDeferredCall([&] () {
        if (screens.size() > 1) {
            screens.back()->pause();
            screens.pop_back();
            screens.back()->resume();
        } else {
            // TODO: Question dialog about exit from game
            PRINT("Exit question dialog")
        }
    });
}

void Window::setScreen(const std::shared_ptr<Screen>& screen) {
    if (screens.empty()) {
        pushScreen(screen);
        return;
    }
    addDeferredCall([=, this] () {
        screens.back()->pause();
        screens.clear();
        pushScreen(screen);
    });
}

Screen* Window::getCurrentScreen() const {
    return screens.size() ? screens.back().get() : nullptr;
}

void Window::show() {
    assert(handle != nullptr);
    SDL_ShowWindow(handle);
}

void Window::close() {
    int x, y;
    SDL_GetWindowPosition(handle, &x, &y);

    Settings::getStorage()["x"] = x;
    Settings::getStorage()["y"] = y;

    Settings::getStorage()["width"] = width;
    Settings::getStorage()["height"] = height;

    SDL_DestroyWindow(handle);
}

void Window::update(float dt) {
    screens.back()->update(dt);
    Overlay::get()->update(dt);
}

void Window::render() {
    screens.back()->draw();
    Overlay::get()->draw();
    RenderManager::get()->draw();

    if (screens.back()->getDirty() || Overlay::get()->getDirty()) {
        RenderManager::get()->markDirty();
        screens.back()->clearDirty();
        Overlay::get()->clearDirty();
    }

    RenderManager::get()->render();

    UIRenderer::get()->clearBatches();
    SceneRenderer::get()->clearViews();
}

void Window::onResize(int width, int height) {
    this->width = width;
    this->height = height;

    for (const auto& screen : screens) {
        screen->resize(width, height);
    }

    Overlay::get()->resize(width, height);

    if (Game::isRunning()) {
        RenderManager::get()->resize();
    }
}

void Window::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(handle) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(handle, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void Window::setColor(const Color& color) {
    this->color = color;
}

void Window::invokeDeffered() {
    for (const auto& call : deferredCalls) {
        call();
    }

    deferredCalls.clear();
}

void Window::onKeyPressed(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
#ifdef DEBUG_HUD_ENABLE
        case SDLK_F5:
            Overlay::get()->toggleDebugHUD();
            Input::get()->isKeyAccepted = true;
            break;
#endif
        case SDLK_F10:
            toggleFullScreen();
            Input::get()->isKeyAccepted = true;
            break;
        case SDLK_F11:
            RenderManager::get()->saveScreenshot();
            Input::get()->isKeyAccepted = true;
            break;
        case SDLK_SLASH:
            if (!Overlay::get()->isDialogOpen() && !Overlay::get()->getConsole()->getVisible()) {
                Overlay::get()->showConsole();
                Input::get()->isKeyAccepted = true;
            }
            break;
    }
}
