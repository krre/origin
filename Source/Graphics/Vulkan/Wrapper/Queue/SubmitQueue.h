#pragma once
#include "Queue.h"
#include <vector>

namespace Vulkan {

class Fence;
class Semaphore;
class CommandBuffer;

class SubmitQueue : public Queue {

public:
    SubmitQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    void submit(Fence* fence = nullptr);
    void waitIdle();

    void addSignalSemaphore(Semaphore* semaphore);
    void addWaitSemaphore(Semaphore* semaphore, VkPipelineStageFlags waitDstStageMask);
    void setWaitSemaphore(Semaphore* semaphore, VkPipelineStageFlags waitDstStageMask);
    void addCommandBuffer(CommandBuffer* commandBuffer);
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
