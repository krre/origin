#pragma once
#include "Graphics/Render/RenderManager.h"

class RenderWindow;

class OpenGLRenderManager : public RenderManager {

public:
    OpenGLRenderManager();
    std::shared_ptr<RenderWindow> createRenderWindow() override;
    void setClearColor(const Color& color) override;
};
