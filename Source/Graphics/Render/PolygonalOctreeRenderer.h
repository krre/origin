#pragma once
#include "OctreeRenderer.h"
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace Origin {

class PolygonalOctreeRenderer : public OctreeRenderer {

public:
    PolygonalOctreeRenderer(Object* parent = nullptr);
    ~PolygonalOctreeRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    void draw() override;
    void drawView(View3D* view) override;

    void setVertexCount(uint32_t vertextCount);
    void updateMvp(const glm::mat4& mvp);

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;

};

} // Origin
