#pragma once
#include "Queue.h"
#include <vector>

namespace Vulkan {

class SubmitQueue : public Queue {

public:
    SubmitQueue(uint32_t queueFamilyIndex, uint32_t queueIndex = 0, Device* device = nullptr);
    VkResult submit(VkFence fence = VK_NULL_HANDLE);
    VkResult waitIdle();

    void addSignalSemaphore(VkSemaphore semaphore);
    void addWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags waitDstStageMask);
    void setWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags waitDstStageMask);
    void addCommandBuffer(VkCommandBuffer commandBuffer);
    void clearCommandBuffers();
    void append();

private:
    VkSubmitInfo submitInfo = {};
    std::vector<VkSemaphore> signalSemaphores;
    std::vector<VkPipelineStageFlags> waitDstStageMasks;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSubmitInfo> submitInfos;

};

} // Vulkan
