#include "OpenGLRenderContext.h"
#include "OpenGLRenderWindow.h"
#include "OpenGLRenderer.h"
#include "OpenGLGpuBuffer.h"
#include "OpenGLTexture.h"
#include "OpenGLShaderProgram.h"
#include <GL/glew.h>

namespace Origin {

OpenGLRenderContext::OpenGLRenderContext() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glewExperimental = GL_TRUE;
}

OpenGLRenderContext::~OpenGLRenderContext() {
    SDL_GL_DeleteContext(context);
}

std::shared_ptr<RenderWindow> OpenGLRenderContext::createRenderWindow() {
    std::shared_ptr<RenderWindow> window = std::make_shared<OpenGLRenderWindow>();
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

std::shared_ptr<GpuBuffer> OpenGLRenderContext::createGpuBuffer(GpuBuffer::Usage usage, uint32_t size) {
    return std::make_shared<OpenGLGpuBuffer>(usage, size);
}

std::shared_ptr<Texture> OpenGLRenderContext::createTexture(const std::string& path) {
    return std::make_shared<OpenGLTexture>(path);
}

std::shared_ptr<ShaderProgram> OpenGLRenderContext::createShaderProgram() {
    return std::make_shared<OpenGLShaderProgram>();
}

std::shared_ptr<Renderer> OpenGLRenderContext::createRenderer() {
    return std::make_shared<OpenGLRenderer>();
}

} // Origin
