#include "SDLWrapper.h"
#include "base/Game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <stdexcept>

#if defined(OS_LINUX)
#include <X11/Xlib-xcb.h>
#endif

namespace {
    bool inited = false;
}

namespace SDL {

void init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL could not initialize!\nSDL_Error: " + error());
    }

    inited = true;
}

void shutdown() {
    SDL_Quit();
}

Core::Size screenSize() {
    Core::Size screenSize;

    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    auto mode = SDL_GetDesktopDisplayMode(display);

    if (!mode) {
        throw std::runtime_error("SDL_GetDesktopDisplayMode failed\nSDL_Error: " + error());
    } else {
        screenSize.width = (*mode).w;
        screenSize.height = (*mode).h;
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
    Platform result = {};

#if defined(OS_WIN)
    result.handle = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
#elif defined(OS_LINUX)

    if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
        SDL_PropertiesID properties = SDL_GetWindowProperties(window);
        Display* display = static_cast<Display*>(SDL_GetPointerProperty(properties, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr));
        const Uint64 windowId = SDL_GetNumberProperty(properties, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);

        if (display == nullptr || windowId == 0) {
            throw std::runtime_error("SDL did not provide X11 window properties: " + error());
        }

        xcb_connection_t* connection = XGetXCBConnection(display);

        if (connection == nullptr) {
            throw std::runtime_error("Could not obtain XCB connection from X11 display");
        }

        result.handle = connection;
        result.window = reinterpret_cast<void*>(static_cast<uintptr_t>(windowId));
    } else if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
        result.handle = (struct wl_display*)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL);
        result.window = (struct wl_surface*)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL);
    }
#endif

    return result;
}

}
