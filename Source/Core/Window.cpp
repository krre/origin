#include "Window.h"

Window::Window() {

}

void Window::setWidth(int width) {
    this->width = width;
}

void Window::setHeight(int height) {
    this->height = height;
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}
