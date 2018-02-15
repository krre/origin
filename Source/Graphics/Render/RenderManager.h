#pragma once
#include "Core/Object.h"
#include "Vulkan/Renderer.h"

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
    UIRenderer* uiRenderer;
    std::vector<RenderPassResource*> renderPassResources;
};

} // Origin
