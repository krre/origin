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
    std::vector<VkSemaphore> m_submitWaitSemaphores;
    std::vector<VkSemaphore> m_submitSignalSemaphores;
    std::vector<VkPipelineStageFlags> m_submitWaitDstStageMasks;
    std::vector<VkSemaphore> m_presentWaitSemaphores;
    std::vector<VkCommandBuffer> m_commandBuffers;
    std::vector<VkSubmitInfo> m_submitInfos;
    VkPresentInfoKHR m_presentInfo = {};
    std::vector<VkSwapchainKHR> m_swapchainHandles;
    std::vector<Swapchain*> m_swapchains;
    std::vector<uint32_t> m_imageIndices;
};

}
