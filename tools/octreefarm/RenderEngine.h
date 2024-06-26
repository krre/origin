#pragma once
#include <vulkan/Renderer.h>
#include <QObject>
#include <QScopedPointer>
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

class RenderEngine : public QObject, public Vulkan::Renderer {
    Q_OBJECT
public:
    RenderEngine(void* platformHandle, void* platformWindow, QObject* parent = nullptr);
    virtual ~RenderEngine();

    Vulkan::GpuBuffer* voxelVertexBuffer() const { return m_voxelRenderPass.vertexBuffer.data(); }
    void setVoxelVertextCount(uint32_t vertexCount);

    Vulkan::GpuBuffer* lineVertexBuffer() const { return m_lineRenderPass.vertexBuffer.data(); }
    void setLineVertextCount(uint32_t vertexCount);

    void updateMvp(const glm::mat4& mvp);
    void updateShadeless(bool shadeless);

private:
    struct RenderPass {
        QScopedPointer<Vulkan::GpuBuffer> vertexBuffer;
        QScopedPointer<Vulkan::GpuBuffer> uboBuffer;
        QScopedPointer<Vulkan::ShaderProgram> shaderProgram;
        QScopedPointer<Vulkan::GraphicsPipeline> graphicsPipeline;
        uint32_t vertextCount = 0;
    };

    void init() override;
    void initVoxelRenderPass();
    void initLineRenderPass();
    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    void updateVoxelUbo();

    struct VoxelUBO {
        glm::mat4 mvp = glm::mat4(1.0);
        int shadeless = 0;
    } m_voxelUbo;


    struct LineUBO {
        glm::mat4 mvp = glm::mat4(1.0);
    } m_lineUbo;

    RenderPass m_voxelRenderPass;
    RenderPass m_lineRenderPass;
};
