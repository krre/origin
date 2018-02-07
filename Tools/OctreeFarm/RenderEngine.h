#pragma once
#include "VulkanRenderer/Renderer.h"

namespace OctreeFarm {

class RenderManager : public Vulkan::Renderer {

public:
    RenderManager(void* platformHandle, void* platformWindow);
    virtual ~RenderManager();

private:
    void init() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
};

} // OctreeFarm
