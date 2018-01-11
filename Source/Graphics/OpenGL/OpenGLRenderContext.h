#pragma once
#include "Graphics/RenderContext.h"
#include <SDL.h>

namespace Origin {

class OpenGLRenderContext : public RenderContext {

public:
    OpenGLRenderContext();
    ~OpenGLRenderContext();
    RenderWindow* createRenderWindow() override;
    Renderer* createRenderer() override;

private:
    SDL_GLContext context;
};

} // Origin
