#pragma once
#include "Core/SingleObject.h"
#include "Vulkan/Renderer.h"

namespace Origin {

class Window;
class Screen;
class ShaderProgram;
class RenderPassResource;
class UIRenderer;
class SceneRenderer;

class RenderManager : public Vulkan::Renderer, public SingleObject<RenderManager> {

public:
    RenderManager(void* platformHandle, void* platformWindow, Object* parent = nullptr);
    ~RenderManager();

    UIRenderer* getUIRenderer() { return get()->uiRenderer; }
    SceneRenderer* getSceneRenderer() { return get()->sceneRenderer; }

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Window* window = nullptr;
    Screen* currentScreen = nullptr;
    UIRenderer* uiRenderer = nullptr;
    SceneRenderer* sceneRenderer = nullptr;
    std::vector<RenderPassResource*> renderPassResources;
};

} // Origin
