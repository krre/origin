#pragma once
#include "Core/Common.h"

namespace Vulkan {
    class CommandBuffer;
    class Framebuffer;
    class RenderPass;
    class Device;
}

namespace Origin {

class RenderPassResource {

public:
    RenderPassResource(Vulkan::Device* device);
    ~RenderPassResource();
    virtual void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) = 0;

protected:
    std::unique_ptr<Vulkan::RenderPass> renderPass;
};

} // Origin
