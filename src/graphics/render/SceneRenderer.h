#pragma once
#include "Renderer.h"

class View3D;
class OctreeRenderer;
class View3DBatch;

class SceneRenderer : public Renderer {
public:
    SceneRenderer(Object* parent = nullptr);

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    static SceneRenderer* get();

    void draw() override;
    bool active() const override;

    void addView(View3D* view);
    void clearViews();

private:
    std::vector<View3D*> m_views;
    std::vector<View3DBatch> m_batches;
    OctreeRenderer* m_octreeRenderer = nullptr;
};
