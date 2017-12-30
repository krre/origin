#include "OpenGLContext.h"
#include "OpenGLRenderWindow.h"

OpenGLContext::OpenGLContext() {

}

OpenGLContext::~OpenGLContext() {

}

RenderWindow* OpenGLContext::createRenderWindowImpl() {
    return new OpenGLRenderWindow;
}
