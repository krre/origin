#pragma once
#include <core/Object.h>

namespace Vulkan {
    class CommandBuffer;
    class Framebuffer;
    class Device;
}

class Renderer : public Core::Object {
public:
    Renderer(Object* parent = nullptr);
    ~Renderer();

    virtual void writeCommandBuffer(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) = 0;
    virtual void draw() = 0;

    void setActive(bool active);
    virtual bool active() const { return m_active; }

    Vulkan::Device* device() const { return m_device; }

private:
    Vulkan::Device* m_device = nullptr;
    bool m_active = true;
};
