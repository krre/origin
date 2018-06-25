#pragma once
#include "RenderLayer.h"
#include <glm/glm.hpp>

namespace Vulkan {
    class GpuBuffer;
    class ShaderProgram;
    class GraphicsPipeline;
}

namespace Origin {

class RenderLayerDebug : public RenderLayer {

public:
    RenderLayerDebug(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderLayerDebug();

    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }
    void resizeVertexBuffer(uint32_t size);
    void setVertexCount(uint32_t vertextCount);

    void updateMvp(const glm::mat4& mvp);

private:
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
        std::unique_ptr<Vulkan::GpuBuffer> uboBuffer;
    std::unique_ptr<Vulkan::ShaderProgram> shaderProgram;
    std::unique_ptr<Vulkan::GraphicsPipeline> graphicsPipeline;
    uint32_t vertextCount = 0;

};

} // Origin
