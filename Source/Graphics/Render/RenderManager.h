#pragma once
#include "Core/SingleObject.h"
#include "Vulkan/Renderer.h"

namespace Origin {

class Screen;
class RenderPassResource;
class Renderer;

class RenderManager : public Vulkan::Renderer, public SingleObject<RenderManager> {

public:
    RenderManager(void* platformHandle, void* platformWindow, Object* parent = nullptr);
    ~RenderManager();

    void addRenderer(Origin::Renderer* renderer);
    void draw();

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Screen* currentScreen = nullptr;
    std::vector<Origin::Renderer*> renderers;
};

} // Origin
