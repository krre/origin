#pragma once
#include "Graphics/GraphicsContext.h"

class OpenGLContext : public GraphicsContext {

public:
    OpenGLContext();
    ~OpenGLContext();
    RenderWindow* createRenderWindow() override;

private:

};
