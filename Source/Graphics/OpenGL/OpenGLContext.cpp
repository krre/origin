#include "OpenGLContext.h"
#include "OpenGLRenderWindow.h"
#include <GL/glew.h>

OpenGLContext::OpenGLContext() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glewExperimental = GL_TRUE;
}

OpenGLContext::~OpenGLContext() {
    SDL_GL_DeleteContext(context);
}

RenderWindow* OpenGLContext::createRenderWindow() {
    RenderWindow* window = new OpenGLRenderWindow;
    window->init();

    context = SDL_GL_CreateContext(window->getHandle());

    if (context == nullptr) {
        throw std::runtime_error(std::string("OpenGL context could not be created\n") + SDL_GetError());
    }

    if (!SDL_GL_ExtensionSupported("GL_ARB_shader_storage_buffer_object") || !SDL_GL_ExtensionSupported("GL_ARB_compute_shader")) {
        throw std::runtime_error(std::string("OpenGL 4.3 is not supported"));
    }

    SDL_GL_MakeCurrent(window->getHandle(), context);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        throw std::runtime_error(std::string("GLEW init failed: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
    }

    return window;
}
