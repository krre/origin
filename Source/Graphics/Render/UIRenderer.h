#pragma once
#include "Renderer.h"
#include "UI/UIBatch.h"

namespace Vulkan {
    class GpuBuffer;
    class Sampler;
    class ShaderProgram;
    class GraphicsPipeline;
    class Texture;
}

namespace Origin {

class UIRenderer : public Renderer {

public:
    UIRenderer(Object* parent = nullptr);
    ~UIRenderer();

    void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    static UIRenderer* get();

    void draw() override;
    bool getActive() const override;

    void addBatch(UIBatch batch);
    void clearBatches();

    std::vector<UIBatch::Vertex>* getVerticles() { return &vertices; }

    void resizeVertexBuffer(uint32_t size);
    void setVertexCount(uint32_t vertextCount);

private:
    std::vector<UIBatch> batches;
    std::vector<UIBatch::Vertex> vertices;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::Sampler> sampler;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
    Vulkan::Texture* texture;
};

} // Origin
