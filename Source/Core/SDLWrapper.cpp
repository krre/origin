#include "SDLWrapper.h"
#include "Defines.h"
#include <SDL.h>
#include <stdexcept>

namespace Origin {

bool SDLWrapper::inited = false;

void SDLWrapper::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::runtime_error("SDL could not initialize!\nSDL_Error: " + getError());
    }

    inited = true;
}

void SDLWrapper::shutdown() {
    SDL_Quit();
}

Size SDLWrapper::getScreenSize() {
    Size screenSize;
    SDL_DisplayMode mode;
    if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
        std::runtime_error("SDL_GetDesktopDisplayMode failed\nSDL_Error: " + getError());
    } else {
        screenSize.width = mode.w;
        screenSize.height = mode.h;
    }

    if (SDL_GetDisplayMode(0, 0, &mode) != 0) {
        std::runtime_error("SDL_GetDisplayMode failed\nSDL_Error: " + getError());
    }
    return screenSize;
}

std::string SDLWrapper::getError() {
    return std::string(SDL_GetError());
}

void SDLWrapper::showErrorMessageBox(const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, APP_NAME, message, nullptr);
}

} // Origin

