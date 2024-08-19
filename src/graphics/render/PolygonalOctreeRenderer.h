#pragma once
#include "OctreeRenderer.h"
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

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
    std::unique_ptr<Vulkan::GpuBuffer> m_vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_uboBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> m_shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> m_graphicsPipeline;
    uint32_t m_vertextCount = 0;
};
