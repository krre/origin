#include "OpenGLRenderWindow.h"
#include <SDL_video.h>
#include <GL/glew.h>
#include <lodepng/lodepng.h>

OpenGLRenderWindow::OpenGLRenderWindow() {

}

OpenGLRenderWindow::~OpenGLRenderWindow() {

}

void OpenGLRenderWindow::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_GL_SwapWindow(handle);
}

void OpenGLRenderWindow::onResize(int width, int height) {
    // TODO: Add implementation
    RenderWindow::onResize(width, height);
}

void OpenGLRenderWindow::saveScreenshotImpl(const std::string& filePath) {
    unsigned char* image = new unsigned char[width * height * 4];
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Vertically flip
    for (unsigned y = 0; y < height / 2; y++) {
        unsigned swapY = height - y - 1;
        for(unsigned x = 0; x < width; x++) {
            unsigned offset = 4 * (x + y * width);
            unsigned swapOffset = 4 * (x + swapY * width);
            unsigned char temp;

            for (int channel = 0; channel <= 3; channel++ ) {
                temp = image[offset + channel];
                image[offset + channel] = image[swapOffset + channel];
                image[swapOffset + channel] = temp;
            }
        }
    }

    lodepng::encode(filePath, image, width, height);

    delete[] image;

}

Uint32 OpenGLRenderWindow::getSurfaceFlag() const {
    return SDL_WINDOW_OPENGL;
}

void OpenGLRenderWindow::initImpl() {
    glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}
