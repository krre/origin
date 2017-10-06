#include "OpenGLRenderManager.h"
#include "OpenGLRenderWindow.h"

OpenGLRenderManager::OpenGLRenderManager() {
    setName("OpenGLRenderManager");
}

RenderWindow* OpenGLRenderManager::createRenderWindow() {
    return new OpenGLRenderWindow;
}
