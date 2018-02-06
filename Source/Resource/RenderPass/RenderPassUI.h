#pragma once
#include "RenderPassResource.h"

namespace Vulkan {
    class RenderPass;
    class GpuBuffer;
    class Sampler;
    class ShaderProgram;
    class GraphicsPipeline;
    class Texture;
}

namespace Origin {

class RenderPassUI : public RenderPassResource {

public:
    RenderPassUI(Vulkan::Device* device);
    ~RenderPassUI();
    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }
    void resizeVertexBuffer(uint32_t size);
    void setVertexCount(uint32_t vertextCount) { this->vertextCount = vertextCount; }
    void setTexture(Vulkan::Texture* texture);

private:
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::Sampler> sampler;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
    Vulkan::Texture* texture;
};

} // Origin
