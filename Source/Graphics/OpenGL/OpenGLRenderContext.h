#pragma once
#include "Graphics/RenderContext.h"
#include <SDL.h>

namespace Origin {

class OpenGLRenderContext : public RenderContext {

public:
    OpenGLRenderContext();
    ~OpenGLRenderContext();
    std::shared_ptr<RenderWindow> createRenderWindow() override;

private:
    std::shared_ptr<Renderer> createRenderer() override;

    SDL_GLContext context;
};

#define glCtx static_cast<OpenRenderContext*>(RenderContext::get())

} // Origin
