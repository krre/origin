#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include <vector>

namespace Origin {

namespace Vulkan {

class Semaphore;
class Fence;
class Swapchain;
class CommandBuffer;

class Queue : public Handle<VkQueue>, public Devicer {

public:
    Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    void create() override {}
    void destroy() override {}

    void addPresentWaitSemaphore(Semaphore* semaphore);
    void clearPresentWaitSemaphores();

    void addCommandBuffer(CommandBuffer* commandBuffer, Semaphore* signalSemaphore = nullptr, Semaphore* waitSemaphore = nullptr, VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT);
    void clearCommandBuffers();

    void addSwapchain(Swapchain* swapchain);
    void clearSwapchains();

    void submit(Fence* fence = nullptr);
    void present(uint32_t* indices = nullptr);

    void waitIdle();
    void syncHost(Fence* fence);

protected:
    std::vector<VkSemaphore> submitWaitSemaphores;
    std::vector<VkSemaphore> submitSignalSemaphores;
    std::vector<VkPipelineStageFlags> submitWaitDstStageMasks;
    std::vector<VkSemaphore> presentWaitSemaphores;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSubmitInfo> submitInfos;
    VkPresentInfoKHR presentInfo = {};
    std::vector<VkSwapchainKHR> swapchainHandles;
    std::vector<Swapchain*> swapchains;
    std::vector<uint32_t> imageIndices;
};

} // Vulkan

} // Origin
