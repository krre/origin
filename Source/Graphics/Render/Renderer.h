#pragma once
#include "Core/Object.h"

namespace Vulkan {
    class CommandBuffer;
    class Framebuffer;
    class Device;
}

namespace Origin {

class Renderer : public Object {

public:
    Renderer(Object* parent = nullptr);
    ~Renderer();

    virtual void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) = 0;
    virtual void draw() = 0;

    void setActive(bool active);
    virtual bool getActive() const { return active; }

    Vulkan::Device* getDevice() const { return device; }

private:
    Vulkan::Device* device = nullptr;
    bool active = true;
};

} // Origin
