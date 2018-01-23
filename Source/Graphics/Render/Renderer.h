#pragma once
#include "Core/Common.h"
#include "Graphics/Render/RenderState.h"
#include "VulkanRenderer/ShaderProgram.h"

namespace Vulkan {
    class ShaderProgram;
}

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
    void createShaderPrograms();

    std::unique_ptr<Renderer2D> renderer2d;
    std::unique_ptr<Renderer3D> renderer3d;

    std::map<Vulkan::ShaderProgram::ProgamType, std::shared_ptr<Vulkan::ShaderProgram>> shaderPrograms;
    std::map<RenderState::Type, std::shared_ptr<RenderState>> renderStates;
};

} // Origin
