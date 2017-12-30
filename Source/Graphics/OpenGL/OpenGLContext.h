#pragma once
#include "Graphics/GraphicsContext.h"
#include <SDL.h>

class OpenGLContext : public GraphicsContext {

public:
    OpenGLContext();
    ~OpenGLContext();
    RenderWindow* createRenderWindow() override;

private:
    SDL_GLContext context;
};
