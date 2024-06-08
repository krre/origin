#include "Window.h"
#include "base/Game.h"
#include "base/Settings.h"
#include "base/Defines.h"
#include "screen/Screen.h"
#include "base/Game.h"
#include "event/Event.h"
#include "event/Input.h"
#include "ui/Overlay.h"
#include "debug/Console.h"
#include "graphics/render/RenderManager.h"
#include "graphics/render/SceneRenderer.h"
#include "graphics/render/UIRenderer.h"
#include <core/Defines.h>
#include <lodepng/lodepng.h>
#include <SDL.h>

Window::Window(Object* parent) : SingleObject(parent) {
    json settingsWidth = Settings::storage()["width"];
    json settingsHeigth = Settings::storage()["height"];

    if (!settingsWidth.is_null()) {
        m_width = settingsWidth.get<int>();
    }

    if (!settingsHeigth.is_null()) {
        m_height = settingsHeigth.get<int>();
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

    m_handle = SDL_CreateWindow(Game::Name, x, y, m_width, m_height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);

    if (m_handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }

    Event::get()->windowResize.connect(this, &Window::onResize);
    Event::get()->keyPressed.connect(this, &Window::onKeyPressed);
}

Window::~Window() {

}

void Window::pushScreen(const std::shared_ptr<Screen>& screen) {
    if (!m_screens.empty()) {
        m_screens.back()->pause();
    }
    m_screens.push_back(screen);
    screen->resize(m_width, m_height);
    screen->resume();
}

void Window::popScreen() {
    addDeferredCall([&] () {
        if (m_screens.size() > 1) {
            m_screens.back()->pause();
            m_screens.pop_back();
            m_screens.back()->resume();
        } else {
            // TODO: Question dialog about exit from game
            PRINT("Exit question dialog")
        }
    });
}

void Window::setScreen(const std::shared_ptr<Screen>& screen) {
    if (m_screens.empty()) {
        pushScreen(screen);
        return;
    }
    addDeferredCall([=, this] () {
        m_screens.back()->pause();
        m_screens.clear();
        pushScreen(screen);
    });
}

Screen* Window::currentScreen() const {
    return m_screens.size() ? m_screens.back().get() : nullptr;
}

void Window::show() {
    assert(m_handle != nullptr);
    SDL_ShowWindow(m_handle);
}

void Window::close() {
    int x, y;
    SDL_GetWindowPosition(m_handle, &x, &y);

    Settings::storage()["x"] = x;
    Settings::storage()["y"] = y;

    Settings::storage()["width"] = m_width;
    Settings::storage()["height"] = m_height;

    SDL_DestroyWindow(m_handle);
}

void Window::update(float dt) {
    m_screens.back()->update(dt);
    Overlay::get()->update(dt);
}

void Window::render() {
    m_screens.back()->draw();
    Overlay::get()->draw();
    RenderManager::get()->draw();

    if (m_screens.back()->dirty() || Overlay::get()->dirty()) {
        RenderManager::get()->markDirty();
        m_screens.back()->clearDirty();
        Overlay::get()->clearDirty();
    }

    RenderManager::get()->render();

    UIRenderer::get()->clearBatches();
    SceneRenderer::get()->clearViews();
}

void Window::onResize(int width, int height) {
    m_width = width;
    m_height = height;

    for (const auto& screen : m_screens) {
        screen->resize(width, height);
    }

    Overlay::get()->resize(width, height);

    if (Game::isRunning()) {
        RenderManager::get()->resize();
    }
}

void Window::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(m_handle) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(m_handle, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void Window::setColor(const Color& color) {
    this->m_color = color;
}

void Window::invokeDeffered() {
    for (const auto& call : m_deferredCalls) {
        call();
    }

    m_deferredCalls.clear();
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
            if (!Overlay::get()->isDialogOpen() && !Overlay::get()->console()->visible()) {
                Overlay::get()->showConsole();
                Input::get()->isKeyAccepted = true;
            }
            break;
    }
}
