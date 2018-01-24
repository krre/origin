#pragma once
#include "VulkanRenderer/Renderer.h"

namespace OctreeFarm {

class VulkanRenderer : public Vulkan::Renderer {

public:
    VulkanRenderer(WindowSettings windowSettings);
    ~VulkanRenderer();

private:
    void prepare() override;
    void init() override;
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer, Vulkan::Framebuffer* framebuffer) override;
};

} // OctreeFarm
