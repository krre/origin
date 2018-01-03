#pragma once
#include "Graphics/GraphicsContext.h"
#include <SDL.h>

namespace Origin {

class OpenGLContext : public GraphicsContext {

public:
    OpenGLContext();
    ~OpenGLContext();
    RenderWindow* createRenderWindow() override;
    Renderer* createRenderer() override;

private:
    SDL_GLContext context;
};

} // Origin
