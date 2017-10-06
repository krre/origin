#pragma once
#include "Graphics/render/RenderManager.h"

class RenderWindow;

class OpenGLRenderManager : public RenderManager {

public:
    OpenGLRenderManager();
    RenderWindow* createRenderWindow() override;
};
