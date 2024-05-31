#pragma once
#include "Renderer.h"
#include "ui/UIBatch.h"

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
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> m_vertices;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> indirectBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::Sampler> sampler;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    Vulkan::Texture* texture;
};
