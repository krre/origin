#include "OpenGLRenderManager.h"
#include "OpenGLRenderWindow.h"
#include <GL/glew.h>

OpenGLRenderManager::OpenGLRenderManager() {
    setName("OpenGLRenderManager");
    glewExperimental = GL_TRUE;
    glewInit();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

std::shared_ptr<RenderWindow> OpenGLRenderManager::createRenderWindow() {
    return std::make_shared<OpenGLRenderWindow>();
}

void OpenGLRenderManager::setClearColor(const Color& color) {

}
