#include "RenderWindow.h"
#include "Core/Common.h"
#include "Core/App.h"
#include "Core/SDLWrapper.h"
#include "Core/Settings.h"
#include "Event/Event.h"
#include "Scene/SceneManager.h"
#include "Graphics/Vulkan/Wrapper/Instance.h"
#include <SDL_video.h>
#include <stdexcept>

RenderWindow::RenderWindow() {
    int screenWidth = SDLWrapper::get()->getScreenSize().width;
    int screenHeight = SDLWrapper::get()->getScreenSize().height;

    std::string settingsWidth = Settings::get()->getValue("width");
    std::string settingsHeigth = Settings::get()->getValue("height");

    width = settingsWidth.empty() ? WINDOW_WIDTH : std::stoi(settingsWidth);
    height = settingsHeigth.empty() ? WINDOW_HEIGHT : std::stoi(settingsHeigth);

    std::string settingsX = Settings::get()->getValue("x");
    std::string settingsY = Settings::get()->getValue("y");

    x = settingsX.empty() ? (screenWidth - width) / 2 : std::stoi(settingsX);
    y = settingsY.empty() ? (screenHeight - height) / 2 : std::stoi(settingsY);

    // Check dual monitor, and if current screen width is larger then maximum monitor resolution,
    // then divide it on 2
//    if (screenWidth > mode.w) {
//        screenWidth /= 2;
//    }

    Event::get()->windowMove.connect<RenderWindow, &RenderWindow::onMove>(this);
    Event::get()->windowResize.connect<RenderWindow, &RenderWindow::onResize>(this);
}

RenderWindow::~RenderWindow() {
    SDL_DestroyWindow(handle);
}

void RenderWindow::show() {
    assert(handle != nullptr);
    SDL_ShowWindow(handle);
}

void RenderWindow::create() {
    handle = SDL_CreateWindow(GAME_NAME.c_str(), x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }
}

void RenderWindow::onMove(int x, int y) {
    Settings::get()->setValue("x", std::to_string(x));
    Settings::get()->setValue("y", std::to_string(y));
}

void RenderWindow::onResize(int width, int height) {
    Settings::get()->setValue("width", std::to_string(width));
    Settings::get()->setValue("height", std::to_string(height));

    if (App::get()->getIsRunning()) {
        Vulkan::Instance::get()->windowResize(width, height);
        SceneManager::get()->rebuild();
    }
}
