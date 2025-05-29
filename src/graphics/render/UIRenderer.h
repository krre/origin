#pragma once
#include "Renderer.h"
#include "ui/UIBatch.h"
#include <memory>

namespace Vulkan {
    class GpuBuffer;
    class Sampler;
    class ShaderProgram;
    class GraphicsPipeline;
    class Texture;
}

class UIRenderer : public Renderer {
public:
    UIRenderer(Object* parent = nullptr);
    ~UIRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    static UIRenderer* get();

    void draw() override;
    bool active() const override;

    void addBatch(UIBatch batch);
    void clearBatches();

    std::vector<UIBatch::Vertex>* verticles() { return &m_vertices; }

private:
    std::vector<UIBatch> m_batches;
    std::vector<UIBatch::Vertex> m_vertices;
    std::unique_ptr<Vulkan::GpuBuffer> m_vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_indirectBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> m_uboBuffer;
    std::unique_ptr<Vulkan::Sampler> m_sampler;
    std::unique_ptr<Vulkan::ShaderProgram> m_shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> m_graphicsPipeline;
    Vulkan::Texture* m_texture = nullptr;
};
