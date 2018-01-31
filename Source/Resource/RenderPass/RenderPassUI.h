#pragma once
#include "RenderPassResource.h"

namespace Vulkan {
    class RenderPass;
}

namespace Origin {

class RenderPassUI : public RenderPassResource {

public:
    RenderPassUI(Vulkan::Device* device);
    ~RenderPassUI();
    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;

private:
    std::unique_ptr<Vulkan::RenderPass> renderPass;
};

} // Origin
