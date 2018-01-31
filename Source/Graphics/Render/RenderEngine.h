#pragma once
#include "VulkanRenderer/Renderer.h"
#include "VulkanRenderer/ShaderProgram.h"

namespace Origin {

class Window;
class Screen;
class Renderer2D;
class Renderer3D;
class RenderState;
class ShaderProgram;

class RenderEngine : public Vulkan::Renderer {

public:
    RenderEngine(void* platformHandle, void* platformWindow);
    ~RenderEngine();

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    std::map<Vulkan::ShaderProgram::ProgamType, std::shared_ptr<Vulkan::ShaderProgram>> shaderPrograms;

    Window* window = nullptr;
    Screen* currentScreen = nullptr;
};

} // Origin
