#include "OpenGLRenderWindow.h"
#include "Core/Defines.h"
#include <GL/glew.h>

OpenGLRenderWindow::OpenGLRenderWindow() {
    handle = SDL_CreateWindow(APP_NAME, x, y, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (handle == nullptr) {
        throw std::runtime_error(std::string("Window could not be created\n") + SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    context = SDL_GL_CreateContext(handle);

    if (context == nullptr) {
        throw std::runtime_error(std::string("OpenGL context could not be created\n") + SDL_GetError());
    }

    if (!SDL_GL_ExtensionSupported("GL_ARB_shader_storage_buffer_object") || !SDL_GL_ExtensionSupported("GL_ARB_compute_shader")) {
        throw std::runtime_error(std::string("OpenGL 4.3 is not supported.\nUpdate your video driver"));
    }

//    SDL_ShowWindow(handle);

    SDL_GL_MakeCurrent(handle, context);
    glewExperimental = GL_TRUE;
    glewInit();
}

void OpenGLRenderWindow::swapBuffers() {

}

void OpenGLRenderWindow::saveImage(const std::string& filePath) {

}
