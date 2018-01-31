#pragma once
#include "RenderPassResource.h"

namespace Origin {

class RenderPassUI : public RenderPassResource {

public:
    RenderPassUI(Vulkan::Device* device);
    void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
};

} // Origin
