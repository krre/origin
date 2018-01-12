#pragma once
#include "Graphics/Render/Renderer.h"

namespace Origin {

class VulkanRenderWindow;

namespace Vulkan {
    class Semaphore;
    class SubmitQueue;
    class Device;
    class CommandBuffer;
    class CommandBuffers;
}

class VulkanRenderer : public Renderer {

public:
    VulkanRenderer();
    ~VulkanRenderer();
    void updateCommandBuffers();

private:
    void renderQueue() override;

    VulkanRenderWindow* window = nullptr;
    Vulkan::Device* device;
    std::unique_ptr<Vulkan::SubmitQueue> submitQueue;
    std::unique_ptr<Vulkan::CommandBuffers> commandBufferHandlers;
    std::vector<std::unique_ptr<Vulkan::CommandBuffer>> commandBuffers;
};

} // Origin
