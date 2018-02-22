#pragma once
#include "Core/Object.h"

namespace Vulkan {
    class CommandBuffer;
    class Framebuffer;
    class Device;
}

namespace Origin {

class RenderPassResource : public Object {

public:
    RenderPassResource(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderPassResource();
    virtual void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) = 0;

    Vulkan::Device* getDevice() const { return device; }

private:
    Vulkan::Device* device = nullptr;
};

} // Origin
