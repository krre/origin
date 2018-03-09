#pragma once
#include "Vulkan/Renderer.h"
#include <QObject>
#include <QScopedPointer>
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace OctreeFarm {

class RenderEngine : public QObject, public Vulkan::Renderer {
    Q_OBJECT

public:
    RenderEngine(void* platformHandle, void* platformWindow, QObject* parent = nullptr);
    virtual ~RenderEngine();

    Vulkan::GpuBuffer* getVertexBuffer() const { return voxelRenderPass.vertexBuffer.data(); }
    void setVertextCount(uint32_t vertexCount);

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
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    void updateUBO();

    struct VoxelUBO {
        glm::mat4 mvp = glm::mat4(1.0);
        int shadeless = 0;
    } voxelUbo;

    RenderPass voxelRenderPass;
};

} // OctreeFarm
