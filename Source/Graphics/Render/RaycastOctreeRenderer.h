#pragma once
#include "OctreeRenderer.h"

namespace Origin {

class RaycastOctreeRenderer : public OctreeRenderer {

public:
    RaycastOctreeRenderer(Object* parent = nullptr);
    ~RaycastOctreeRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    void draw() override;

private:

};

} // Origin
