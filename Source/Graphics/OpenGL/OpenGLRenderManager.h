#pragma once
#include "Graphics/Render/RenderManager.h"

class RenderWindow;

class OpenGLRenderManager : public RenderManager {

public:
    OpenGLRenderManager();
    RenderWindow* createRenderWindow() override;
};
