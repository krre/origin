#pragma once
#include "Core/Object.h"
#include "VulkanRenderer/Renderer.h"

namespace Origin {

class Window;
class Screen;
class ShaderProgram;
class RenderPassResource;
class UIRenderer;

class RenderManager : public Vulkan::Renderer, public Object {

public:
    RenderManager(void* platformHandle, void* platformWindow, Object* parent = nullptr);
    ~RenderManager();

    UIRenderer* getUIRenderer() const { return uiRenderer; }

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Window* window = nullptr;
    Screen* currentScreen = nullptr;
    std::vector<RenderPassResource*> renderPassResources;
    UIRenderer* uiRenderer;
};

} // Origin
