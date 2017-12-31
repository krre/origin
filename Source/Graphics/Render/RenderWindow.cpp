#include "RenderWindow.h"
#include "Core/Application.h"
#include "Core/SDLWrapper.h"
#include "Core/Settings.h"
#include "Core/Defines.h"
#include "Core/Utils.h"
#include "Core/Screen.h"
#include "Debug/DebugHUD.h"
#include "UI/Toast.h"
#include "Event/Event.h"
#include "Event/Input.h"
#include <SDL_keycode.h>
#include <ctime>
#include <experimental/filesystem>

// Hack to disable typedef Screen from X11 to prevent conflict with Screen class
#define Screen SCREEN_DEF

// TODO: Remove Drawable class from project
#define Drawable DRAWABLE_DEF

#define Font FONT_DEF

#undef Screen
#undef Drawable
#undef Font

#include "Core/Game.h"
#include <SDL_video.h>
#include <lodepng/lodepng.h>

RenderWindow::RenderWindow() {
    auto settingsWidth = Settings::get()->getStorage()["width"];
    auto settingsHeigth = Settings::get()->getStorage()["height"];

    if (!settingsWidth.is_null()) {
        width = settingsWidth.get<int>();
    }

    if (!settingsHeigth.is_null()) {
        height = settingsHeigth.get<int>();
    }

    auto settingsX = Settings::get()->getStorage()["x"];
    auto settingsY = Settings::get()->getStorage()["y"];

    x = settingsX.is_null() ? (SDLWrapper::get()->getScreenSize().width - width) / 2 : settingsX.get<int>();
    y = settingsY.is_null() ? (SDLWrapper::get()->getScreenSize().height - height) / 2 : settingsY.get<int>();
}

RenderWindow::~RenderWindow() {
    Settings::get()->getStorage()["x"] = x;
    Settings::get()->getStorage()["y"] = y;

    Settings::get()->getStorage()["width"] = width;
    Settings::get()->getStorage()["height"] = height;

    SDL_DestroyWindow(handle);
}

void RenderWindow::init() {
    handle = SDL_CreateWindow(APP_NAME, x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | getSurfaceFlag());
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }

    initImpl();

    Event::get()->windowMove.connect(this, &RenderWindow::onMove);
    Event::get()->windowResize.connect(this, &RenderWindow::onResize);
    Event::get()->keyPressed.connect(this, &RenderWindow::onKeyPressed);
}

void RenderWindow::pushScreen(const std::shared_ptr<Screen>& screen) {
    if (!screens.empty()) {
        screens.back()->pause();
    }
    screens.push_back(screen);
    screen->resize(width, height);
    screen->resume();
}

void RenderWindow::popScreen() {
    if (screens.size() > 1) {
        screens.back()->pause();
        screens.pop_back();
        screens.back()->resume();
    } else {
        // TODO: Question dialog about exit from game
        PRINT("Exit question dialog")
    }
}

void RenderWindow::setScreen(const std::shared_ptr<Screen>& screen) {
    for (const auto& screen : screens) {
        screen->pause();
    }
    screens.clear();
    pushScreen(screen);
}

void RenderWindow::show() {
    assert(handle != nullptr);
    SDL_ShowWindow(handle);
}

void RenderWindow::update(float dt) {
    screens.back()->update(dt);
}

void RenderWindow::render() {

}

void RenderWindow::onMove(int x, int y) {
    this->x = x;
    this->y = y;
}

void RenderWindow::onResize(int width, int height) {
    this->width = width;
    this->height = height;

    for (const auto& screen : screens) {
        screen->resize(width, height);
    }
}

void RenderWindow::saveScreenshot() {
    std::string directoryPath = Application::getCurrentPath() + Utils::getPathSeparator() + "Screenshot";
    namespace fs = std::experimental::filesystem;
    if (!fs::exists(directoryPath)) {
        fs::create_directory(directoryPath);
    }

    time_t t = std::time(0); // Get time now
    struct tm* now = std::localtime(&t);
    std::string filename =
            std::to_string(now->tm_year + 1900) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mon + 1)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_mday)) + "_" +
            Utils::zeroFill(std::to_string(now->tm_hour)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_min)) + "-" +
            Utils::zeroFill(std::to_string(now->tm_sec)) + ".png";
    std::string filePath = directoryPath + Utils::getPathSeparator() + filename;
    saveScreenshotImpl(filePath);

    std::string message = "Screenshot saved to " + filename;
//    Toast::get()->showToast(message);
    PRINT(message)
}

void RenderWindow::toggleFullScreen() {
    bool isFullscreen = SDL_GetWindowFlags(handle) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(handle, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
    SDL_ShowCursor(isFullscreen);
}

void RenderWindow::setColor(const Color& color) {
    this->color = color;
}

void RenderWindow::onKeyPressed(const SDL_KeyboardEvent& event) {
    switch (event.keysym.sym) {
#ifdef DEBUG_HUD_ENABLE
    case SDLK_F5:
        DebugHUD::get()->trigger();
        break;
#endif
    case SDLK_F10:
        toggleFullScreen();
        break;
    case SDLK_F11:
        saveScreenshot();
        break;
    }
}
