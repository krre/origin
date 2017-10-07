#include "SDLWrapper.h"
#include "Defines.h"
#include <SDL.h>
#include <stdexcept>

SDLWrapper::SDLWrapper() {

}

SDLWrapper::~SDLWrapper() {
    SDL_Quit();
}

void SDLWrapper::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::runtime_error("SDL could not initialize!\nSDL_Error: " + getError());
    }

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

    isInited = true;
}

std::string SDLWrapper::getError() const {
    return std::string(SDL_GetError());
}

void SDLWrapper::showErrorMessageBox(const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, APP_VERSION_STR, message, nullptr);
}
