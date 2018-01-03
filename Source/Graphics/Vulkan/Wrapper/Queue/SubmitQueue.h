#pragma once
#include "Queue.h"
#include <vector>

namespace Origin {

namespace Vulkan {

class Fence;
class Semaphore;
class CommandBuffer;

class SubmitQueue : public Queue {

public:
    SubmitQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    void submit(Fence* fence = nullptr);
    void addCommandBuffer(CommandBuffer* commandBuffer, Semaphore* waitSemaphore, VkPipelineStageFlags waitDstStageMask, Semaphore* signalSemaphore);
    void addCommandBuffer(CommandBuffer* commandBuffer, Semaphore* signalSemaphore);
    void addCommandBuffer(CommandBuffer* commandBuffer);
    void clearCommandBuffers();

private:
    std::vector<VkSemaphore> signalSemaphores;
    std::vector<VkPipelineStageFlags> waitDstStageMasks;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSubmitInfo> submitInfos;

};

} // Vulkan

} // Origin
