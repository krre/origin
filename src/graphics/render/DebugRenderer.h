#pragma once
#include "Renderer.h"
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

class DebugRenderer : public Renderer {

public:
    DebugRenderer(Object* parent = nullptr);
    ~DebugRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    static DebugRenderer* get();

    void draw() override;

    void setVertexCount(uint32_t vertextCount);
    void updateMvp(const glm::mat4& mvp);

private:
    std::unique_ptr<Vulkan::GpuBuffer> m_vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_uboBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> m_shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> m_graphicsPipeline;
    uint32_t m_vertextCount = 0;

};
