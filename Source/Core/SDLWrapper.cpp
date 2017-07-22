#include "SDLWrapper.h"
#include <SDL.h>
#include <stdexcept>

SDLWrapper::SDLWrapper() {

}

void SDLWrapper::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::runtime_error(std::string("SDL could not initialize!\nSDL_Error: ") + SDL_GetError());
    }

    SDL_DisplayMode mode;
    if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
        std::runtime_error(std::string("SDL_GetDesktopDisplayMode failed\nSDL_Error: ") + SDL_GetError());
    } else {
        screenSize.width = mode.w;
        screenSize.height = mode.h;
    }

    if (SDL_GetDisplayMode(0, 0, &mode) != 0) {
        std::runtime_error(std::string("SDL_GetDisplayMode failed\nSDL_Error: ") + SDL_GetError());
    }
}
