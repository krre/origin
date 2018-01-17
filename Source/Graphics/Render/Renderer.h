#pragma once
#include "Core/Common.h"
#include "Graphics/Render/RenderState.h"

namespace Origin {

class Screen;
class Renderer2D;
class Renderer3D;
class RenderState;

class Renderer {

public:
    Renderer();
    virtual ~Renderer();
    void render(Screen* screen);
    RenderState* getRenderState(RenderState::Type type) { return renderStates[type].get(); }

protected:
    virtual void renderQueue() = 0;

private:
    void createRenderStates();

    std::unique_ptr<Renderer2D> renderer2d;
    std::unique_ptr<Renderer3D> renderer3d;
    std::map<RenderState::Type, std::unique_ptr<RenderState>> renderStates;
};

} // Origin
