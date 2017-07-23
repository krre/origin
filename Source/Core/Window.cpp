#include "Window.h"
#include "Common.h"
#include "SDLWrapper.h"
#include "Settings.h"
#include "Event/Event.h"
#include <SDL_video.h>
#include <stdexcept>

Window::Window() {
    int screenWidth = SDLWrapper::get()->getScreenSize().width;
    int screenHeight = SDLWrapper::get()->getScreenSize().height;

    std::string settingsX = Settings::get()->getValue("x");
    std::string settingsY = Settings::get()->getValue("y");
    std::string settingsWidth = Settings::get()->getValue("width");
    std::string settingsHeigth = Settings::get()->getValue("height");

    x = settingsX.empty() ? (screenWidth - width) / 2 : std::stoi(settingsX);
    y = settingsY.empty() ? (screenHeight - height) / 2 : std::stoi(settingsY);
    width = settingsWidth.empty() ? width : std::stoi(settingsWidth);
    height = settingsHeigth.empty() ? height : std::stoi(settingsHeigth);

    // Check dual monitor, and if current screen width is larger then maximum monitor resolution,
    // then divide it on 2
//    if (screenWidth > mode.w) {
//        screenWidth /= 2;
//    }

    Event::get()->windowMove.connect<Window, &Window::onMove>(this);
}

Window::~Window() {
    SDL_DestroyWindow(handle);
}

void Window::show() {
    if (handle == nullptr) {
        create();
    }

    SDL_ShowWindow(handle);
}

void Window::create() {
    handle = SDL_CreateWindow(GAME_NAME.c_str(), x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }
}

void Window::onMove(int x, int y) {
    Settings::get()->setValue("x", std::to_string(x));
    Settings::get()->setValue("y", std::to_string(y));
}
