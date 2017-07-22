#include "Window.h"
#include <SDL_video.h>
#include <stdexcept>

Window::Window() {

}

void Window::show() {
    if (handle == nullptr) {
        create();
    } else {
        SDL_ShowWindow(handle);
    }
}

void Window::create() {
    handle = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }
}
