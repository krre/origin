#pragma once
#include "RenderLayer.h"

namespace Vulkan {
    class GpuBuffer;
    class Sampler;
    class ShaderProgram;
    class GraphicsPipeline;
    class Texture;
}

namespace Origin {

class RenderLayerUI : public RenderLayer {

public:
    RenderLayerUI(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderLayerUI();

    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }
    void resizeVertexBuffer(uint32_t size);
    void setVertexCount(uint32_t vertextCount);
    void setTexture(Vulkan::Texture* texture);

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::Sampler> sampler;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
    Vulkan::Texture* texture;

};

} // Origin
