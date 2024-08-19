#include "SDLWrapper.h"
#include "base/Game.h"
#include <SDL.h>
#include <SDL_syswm.h>
#include <stdexcept>

#if defined(OS_LINUX)
#include <X11/Xlib-xcb.h>
#endif

namespace {
    bool inited = false;
}

namespace SDL {

void init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("SDL could not initialize!\nSDL_Error: " + error());
    }

    inited = true;
}

void shutdown() {
    SDL_Quit();
}

Core::Size screenSize() {
    Core::Size screenSize;
    SDL_DisplayMode mode;
    if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
        throw std::runtime_error("SDL_GetDesktopDisplayMode failed\nSDL_Error: " + error());
    } else {
        screenSize.width = mode.w;
        screenSize.height = mode.h;
    }

    if (SDL_GetDisplayMode(0, 0, &mode) != 0) {
        throw std::runtime_error("SDL_GetDisplayMode failed\nSDL_Error: " + error());
    }
    return screenSize;
}

std::string error() {
    return std::string(SDL_GetError());
}

void showErrorMessageBox(const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, Game::Name, message, nullptr);
}

bool isInited() {
    return inited;
}

Platform platform(SDL_Window* window) {
    static SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    if (!SDL_GetWindowWMInfo(window, &wminfo)) {
        throw std::runtime_error("SDL_GetWindowWMInfo failed\nSDL_Error: " + error());
    }

    Platform result;

#if defined(OS_WIN)
    result.handle = GetModuleHandle(nullptr);
    result.window = (void*)wminfo.info.win.window;
#elif defined(OS_LINUX)
    result.handle = (void*)XGetXCBConnection(wminfo.info.x11.display);
    result.window = (void*)&wminfo.info.x11.window;
#endif

    return result;
}

}
