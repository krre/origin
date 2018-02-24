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

    struct Vertex {
        glm::vec4 pos;
        glm::vec4 color;
    };

    RenderEngine(void* platformHandle, void* platformWindow, QObject* parent = nullptr);
    virtual ~RenderEngine();

private:
    void init() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    QScopedPointer<Vulkan::GpuBuffer> vertexBuffer;
    QScopedPointer<Vulkan::GpuBuffer> uboBuffer;
    QScopedPointer<Vulkan::ShaderProgram> shaderProgram;
    QScopedPointer<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
};

} // OctreeFarm
