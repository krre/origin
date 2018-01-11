#pragma once
#include "Graphics/RenderContext.h"
#include <SDL.h>

namespace Origin {

class OpenGLRenderContext : public RenderContext {

public:
    OpenGLRenderContext();
    ~OpenGLRenderContext();
    std::shared_ptr<RenderWindow> createRenderWindow() override;
    std::shared_ptr<Renderer> createRenderer() override;

private:
    SDL_GLContext context;
};

} // Origin
