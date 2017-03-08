#pragma once
#include "Queue.h"
#include "../Fence.h"
#include <vector>

namespace Vulkan {

class SubmitQueue : public Queue {

public:
    SubmitQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    VkResult submit(VkFence fence = VK_NULL_HANDLE);
    VkResult waitIdle();

    void addSignalSemaphore(VkSemaphore semaphore);
    void addWaitDstStageMask(VkPipelineStageFlags waitDstStageMask);
    void addCommandBuffer(VkCommandBuffer commandBuffer);
    void clearCommandBuffers();

    VkSubmitInfo submitInfo = {};

private:
    std::vector<VkSemaphore> signalSemaphores;
    std::vector<VkPipelineStageFlags> waitDstStageMasks;
    std::vector<VkCommandBuffer> commandBuffers;

};

} // Vulkan
