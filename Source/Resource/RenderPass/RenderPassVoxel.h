#pragma once
#include "RenderPassResource.h"

namespace Vulkan {
    class GpuBuffer;
    class Sampler;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace Origin {

class RenderPassVoxel : public RenderPassResource {

public:
    RenderPassVoxel(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderPassVoxel();
    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }
    void resizeVertexBuffer(uint32_t size);
    void setVertexCount(uint32_t vertextCount) { this->vertextCount = vertextCount; }

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
};

} // Origin
