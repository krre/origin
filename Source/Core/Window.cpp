#include "Window.h"
#include <SDL_video.h>

Window::Window() {

}

void Window::create() {
    handle = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (handle == nullptr) {
        // TODO: Throw exception
    }
}
