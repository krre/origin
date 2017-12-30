#include "OpenGLRenderWindow.h"

OpenGLRenderWindow::OpenGLRenderWindow() {

}

OpenGLRenderWindow::~OpenGLRenderWindow() {

}

void OpenGLRenderWindow::render() {

}

void OpenGLRenderWindow::onResize(int width, int height) {
    // TODO: Add implementation
    RenderWindow::onResize(width, height);
}

void OpenGLRenderWindow::saveScreenshotImpl(const std::string& filePath) {

}

Uint32 OpenGLRenderWindow::getSurfaceFlag() const {
    return SDL_WINDOW_OPENGL;
}
