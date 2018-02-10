#pragma once
#include "VulkanRenderer/Renderer.h"

namespace OctreeFarm {

class RenderEngine : public Vulkan::Renderer {

public:
    RenderEngine(void* platformHandle, void* platformWindow);
    virtual ~RenderEngine();

private:
    void init() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
};

} // OctreeFarm
