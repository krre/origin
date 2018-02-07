#pragma once
#include "VulkanRenderer/Renderer.h"

namespace Origin {

class Window;
class Screen;
class ShaderProgram;
class RenderPassResource;
class UIRenderer;

class RenderManager : public Vulkan::Renderer {

public:
    RenderManager(void* platformHandle, void* platformWindow);
    ~RenderManager();

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
