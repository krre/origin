#pragma once
#include "vulkan/Renderer.h"
#include <core/SingleObject.h>

class Screen;
class RenderPassResource;
class Renderer;

class RenderManager : public Vulkan::Renderer, public Core::SingleObject<RenderManager> {
public:
    RenderManager(void* platformHandle, void* platformWindow, Object* parent = nullptr);

    void addRenderer(::Renderer* renderer);
    void draw();

    void saveScreenshot();

private:
    void init() override;
    void preRender() override;
    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Screen* m_currentScreen = nullptr;
    std::vector<::Renderer*> m_renderers;
};
