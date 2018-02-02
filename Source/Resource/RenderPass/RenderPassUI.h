#pragma once
#include "RenderPassResource.h"

namespace Vulkan {
    class RenderPass;
    class GpuBuffer;
}

namespace Origin {

class RenderPassUI : public RenderPassResource {

public:
    RenderPassUI(Vulkan::Device* device);
    ~RenderPassUI();
    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
    Vulkan::GpuBuffer* getVertexBuffer() const { return vertexBuffer.get(); }
    void resizeVertexBuffer(uint32_t size);

private:
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::unique_ptr<Vulkan::GpuBuffer> vertexBuffer;
};

} // Origin
