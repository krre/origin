#pragma once
#include "OctreeRenderer.h"

namespace Origin {

class PolygonalOctreeRenderer : public OctreeRenderer {

public:
    PolygonalOctreeRenderer(Object* parent = nullptr);
    ~PolygonalOctreeRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

private:

};

} // Origin
