#include "OpenGLContext.h"
#include "OpenGLRenderWindow.h"
#include <GL/glew.h>

OpenGLContext::OpenGLContext() {
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

//    glewExperimental = GL_TRUE;
//    GLenum err = glewInit();
//    if (err != GLEW_OK) {
//        throw std::runtime_error(std::string("glewInit failed: ") + std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
//    }
}

OpenGLContext::~OpenGLContext() {

}

RenderWindow* OpenGLContext::createRenderWindow() {
    return new OpenGLRenderWindow;
}
