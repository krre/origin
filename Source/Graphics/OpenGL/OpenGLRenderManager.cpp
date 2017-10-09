#include "OpenGLRenderManager.h"
#include "OpenGLRenderWindow.h"

OpenGLRenderManager::OpenGLRenderManager() {
    setName("OpenGLRenderManager");
}

std::shared_ptr<RenderWindow> OpenGLRenderManager::createRenderWindow() {
    return std::make_shared<OpenGLRenderWindow>();
}
