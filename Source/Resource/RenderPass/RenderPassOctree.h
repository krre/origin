#pragma once
#include "RenderPassResource.h"
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace Origin {

class RenderPassOctree : public RenderPassResource {

public:
    RenderPassOctree(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderPassOctree();
    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;
};

} // Origin
