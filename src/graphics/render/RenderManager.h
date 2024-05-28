#pragma once
#include <core/SingleObject.h>
#include "vulkan/Renderer.h"

class Screen;
class RenderPassResource;
class Renderer;

class RenderManager : public Vulkan::Renderer, public Core::SingleObject<RenderManager> {

public:
    RenderManager(void* platformHandle, void* platformWindow, Object* parent = nullptr);
    ~RenderManager();

    void addRenderer(::Renderer* renderer);
    void draw();

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Screen* currentScreen = nullptr;
    std::vector<::Renderer*> renderers;
};
