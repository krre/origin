#pragma once
#include "Graphics/Render/RenderContext.h"
#include <SDL.h>

namespace Origin {

class OpenGLRenderContext : public RenderContext {

public:
    OpenGLRenderContext();
    ~OpenGLRenderContext();
    std::shared_ptr<RenderWindow> createRenderWindow() override;
    std::shared_ptr<GpuBuffer> createGpuBuffer(GpuBuffer::Usage usage, uint32_t size) override;
    std::shared_ptr<Texture> createTexture(const std::string& path) override;
    std::shared_ptr<ShaderProgram> createShaderProgram(const std::string& name) override;

private:
    std::shared_ptr<Renderer> createRenderer() override;

    SDL_GLContext context;
};

#define glCtx static_cast<OpenRenderContext*>(RenderContext::get())

} // Origin
