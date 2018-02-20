#include "Window.h"
#include "Base/Game.h"
#include "Base/SDLWrapper.h"
#include "Base/Settings.h"
#include "Base/Defines.h"
#include "Screen/Screen.h"
#include "Base/Game.h"
#include "Debug/DebugHUD.h"
#include "UI/Toast.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include "Core/Defines.h"
#include "UI/Overlay.h"
#include "Graphics/Render/UIRenderer.h"
#include "Graphics/Render/SceneRenderer.h"
#include "Debug/Console.h"
#include "Graphics/Render/RenderManager.h"
#include <lodepng/lodepng.h>
#include <SDL_syswm.h>
#include <SDL_keycode.h>
#include <ctime>
#include <experimental/filesystem>
#include <SDL_video.h>

namespace Origin {

Window::Window(Object* parent) : Object(parent) {
    auto settingsWidth = Game::getSettings()->getStorage()["width"];
    auto settingsHeigth = Game::getSettings()->getStorage()["height"];

    if (!settingsWidth.is_null()) {
        width = settingsWidth.get<int>();
    }

    if (!settingsHeigth.is_null()) {
        height = settingsHeigth.get<int>();
    }

    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;

// On some Ubuntu OS y position is shifted on window creation, so do not use position settings
#if !defined(OS_LINUX)
    auto settingsX = Game::getSettings()->getStorage()["x"];
    auto settingsY = Game::getSettings()->getStorage()["y"];

    if (!settingsX.is_null() && !settingsY.is_null()) {
        x = settingsX.get<int>();
        y = settingsY.get<int>();
    }
#endif

    handle = SDL_CreateWindow(APP_NAME, x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }

    Game::getEvent()->windowResize.connect(this, &Window::onResize);
    Game::getEvent()->keyPressed.connect(this, &Window::onKeyPressed);
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
    addDeferredCall([=] () {
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

    Game::getSettings()->getStorage()["x"] = x;
    Game::getSettings()->getStorage()["y"] = y;

    Game::getSettings()->getStorage()["width"] = width;
    Game::getSettings()->getStorage()["height"] = height;

    SDL_DestroyWindow(handle);
}

void Window::update(float dt) {
    screens.back()->update(dt);
    Game::getOverlay()->update(dt);
}

void Window::render() {
    screens.back()->draw();
    Game::getOverlay()->draw();
    Game::getRenderManager()->getUIRenderer()->drawBatches();
    Game::getRenderManager()->getSceneRenderer()->drawScenes();

    if (screens.back()->getDirty() || Game::getOverlay()->getDirty()) {
        Game::getRenderManager()->updateCommandBuffers();
        if (screens.back()->getDirty()) {
            screens.back()->clearDirty();
        }
        if (Game::getOverlay()->getDirty()) {
            Game::getOverlay()->clearDirty();
        }
    }

    Game::getRenderManager()->render();
}

void Window::onResize(int width, int height) {
    this->width = width;
    this->height = height;

    for (const auto& screen : screens) {
        screen->resize(width, height);
    }

    Game::getOverlay()->resize(width, height);
    if (Game::isRunning()) {
        Game::getRenderManager()->resize();
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
            Game::getOverlay()->toggleDebugHUD();
            Game::getInput()->isKeyAccepted = true;
            break;
#endif
        case SDLK_F10:
            toggleFullScreen();
            Game::getInput()->isKeyAccepted = true;
            break;
        case SDLK_F11:
            Game::getRenderManager()->saveScreenshot();
            Game::getInput()->isKeyAccepted = true;
            break;
        case SDLK_SLASH:
            if (!Game::getOverlay()->isDialogOpen() && !Game::getOverlay()->getConsole()->getVisible()) {
                Game::getOverlay()->showConsole();
                Game::getInput()->isKeyAccepted = true;
            }
            break;
    }
}

} // Origin
