#include "OpenGLRenderWindow.h"
#include <SDL_video.h>
#include <GL/glew.h>

OpenGLRenderWindow::OpenGLRenderWindow() {

}

OpenGLRenderWindow::~OpenGLRenderWindow() {

}

void OpenGLRenderWindow::render() {
    glClearColor(0.9, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_GL_SwapWindow(handle);
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
