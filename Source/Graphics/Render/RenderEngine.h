#pragma once
#include "VulkanRenderer/Renderer.h"

namespace Origin {

class Window;
class Screen;
class ShaderProgram;
class RenderPassResource;
class UIRenderer;

class RenderEngine : public Vulkan::Renderer {

public:
    RenderEngine(void* platformHandle, void* platformWindow);
    ~RenderEngine();

    UIRenderer* getUIRenderer() const { return uiRenderer.get(); }

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Window* window = nullptr;
    Screen* currentScreen = nullptr;
    std::vector<RenderPassResource*> renderPassResources;
    std::unique_ptr<UIRenderer> uiRenderer;
};

} // Origin
