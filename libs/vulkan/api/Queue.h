#pragma once
#include "base/Handle.h"
#include "device/Devicer.h"
#include <vector>

namespace Vulkan {

class Swapchain;

class Queue : public Handle<VkQueue>, public Devicer {

public:
    Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    void create() override {}
    void destroy() override {}

    void addPresentWaitSemaphore(VkSemaphore semaphore);
    void clearPresentWaitSemaphores();

    void addCommandBuffer(VkCommandBuffer commandBuffer, VkSemaphore signalSemaphore = VK_NULL_HANDLE, VkSemaphore waitSemaphore = VK_NULL_HANDLE, VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT);
    void clearCommandBuffers();

    void addSwapchain(Swapchain* swapchain);
    void clearSwapchains();

    void submit(VkFence fence = VK_NULL_HANDLE);
    void present(uint32_t* indices = VK_NULL_HANDLE);

    void waitIdle();
    void syncHost(VkFence fence);

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
