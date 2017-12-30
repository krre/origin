#pragma once
#include "Graphics/GraphicsContext.h"

class OpenGLContext : public GraphicsContext {

public:
    OpenGLContext();
    ~OpenGLContext();

private:
    RenderWindow* createRenderWindowImpl() override;
};
