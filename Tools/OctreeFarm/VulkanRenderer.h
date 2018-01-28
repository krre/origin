#pragma once
#include "VulkanRenderer/Renderer.h"

namespace OctreeFarm {

class VulkanRenderer : public Vulkan::Renderer {

public:
    VulkanRenderer(void* platformHandle, void* platformWindow);
    virtual ~VulkanRenderer();

private:
    void init() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
};

} // OctreeFarm
