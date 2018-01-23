#pragma once
#include "Core/Common.h"
#include "Graphics/Render/RenderState.h"
#include "VulkanRenderer/ShaderProgram.h"

namespace Origin {

class Screen;
class Renderer2D;
class Renderer3D;
class RenderState;
class ShaderProgram;

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
    void createShaderPrograms();

    std::unique_ptr<Renderer2D> renderer2d;
    std::unique_ptr<Renderer3D> renderer3d;

    std::map<ShaderProgram::ProgamType, std::shared_ptr<ShaderProgram>> shaderPrograms;
    std::map<RenderState::Type, std::shared_ptr<RenderState>> renderStates;
};

} // Origin
