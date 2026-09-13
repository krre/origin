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
        result.handle = (void*)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_X11_DISPLAY_POINTER, NULL);
        result.window = (void*)SDL_GetNumberProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
        // SDL_PropertiesID props = SDL_GetWindowProperties(window);
        // Display* xdisplay = (Display*)SDL_GetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, NULL);

        // // Преобразуем Display* в xcb_connection_t*
        // result.handle = (void*)XGetXCBConnection(xdisplay);

        // // Числовое значение передается без каста к указателю
        // result.window = (uint64_t)SDL_GetNumberProperty(props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
    } else if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {
        result.handle = (struct wl_display*)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL);
        result.window = (struct wl_surface*)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL);
    }
#endif

    return result;
}

}
