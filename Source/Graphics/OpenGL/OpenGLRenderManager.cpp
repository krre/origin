#include "OpenGLRenderManager.h"
#include "OpenGLRenderWindow.h"

OpenGLRenderManager::OpenGLRenderManager() {

}

RenderWindow* OpenGLRenderManager::createRenderWindow() {
    return new OpenGLRenderWindow;
}
