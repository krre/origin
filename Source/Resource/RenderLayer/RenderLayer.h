#pragma once
#include "Core/Object.h"

namespace Vulkan {
    class CommandBuffer;
    class Framebuffer;
    class Device;
}

namespace Origin {

class RenderLayer : public Object {

public:
    RenderLayer(Vulkan::Device* device, Object* parent = nullptr);
    ~RenderLayer();

    virtual void write(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) = 0;

    Vulkan::Device* getDevice() const { return device; }

private:
    Vulkan::Device* device = nullptr;

};

} // Origin
