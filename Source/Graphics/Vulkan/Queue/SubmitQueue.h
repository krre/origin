#pragma once
#include "Queue.h"
#include "../Fence.h"
#include <vector>

namespace Vulkan {

class SubmitQueue : public Queue {

public:
    SubmitQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    VkResult submit(VkFence fence = VK_NULL_HANDLE);

    void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores) override;
    void setSignalSemaphores(std::vector<VkSemaphore> signalSemaphores);
    void setWaitDstStageMask(std::vector<VkPipelineStageFlags> waitDstStageMask);

    void setCommandBuffers(std::vector<VkCommandBuffer> commandBuffers);
    void setCommandBuffers(uint32_t count, const VkCommandBuffer* data);

private:
    VkSubmitInfo submitInfo = {};
    std::vector<VkSemaphore> signalSemaphores;
    std::vector<VkPipelineStageFlags> waitDstStageMask;
    std::vector<VkCommandBuffer> commandBuffers;

};

} // Vulkan
