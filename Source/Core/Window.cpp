#include "Window.h"
#include "Common.h"
#include <SDL_video.h>
#include <stdexcept>

Window::Window() {

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
