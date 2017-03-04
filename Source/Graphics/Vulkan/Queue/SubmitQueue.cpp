#include "SubmitQueue.h"

using namespace Vulkan;

SubmitQueue::SubmitQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}

VkResult SubmitQueue::submit(VkFence fence) {
    submitInfo.waitSemaphoreCount = waitSemaphores.size();
    submitInfo.pWaitSemaphores = waitSemaphores.data();
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = signalSemaphores.data();
    CHECK_RESULT(vkQueueSubmit(handle, 1, &submitInfo, fence), "Failed to submit queue");
    return result;
}

VkResult SubmitQueue::waitIdle() {
    return checkError(vkQueueWaitIdle(handle), "Failed to wait idle for queue");
}

void SubmitQueue::addSignalSemaphore(VkSemaphore semaphore) {
    signalSemaphores.push_back(semaphore);
}

void SubmitQueue::setWaitDstStageMask(std::vector<VkPipelineStageFlags> waitDstStageMask) {
    this->waitDstStageMask = waitDstStageMask;
    submitInfo.pWaitDstStageMask = this->waitDstStageMask.data();
}

void SubmitQueue::setCommandBuffers(std::vector<VkCommandBuffer> commandBuffers) {
    this->commandBuffers = commandBuffers;
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = this->commandBuffers.data();
}

void SubmitQueue::setCommandBuffers(uint32_t count, const VkCommandBuffer* data) {
    submitInfo.commandBufferCount = count;
    submitInfo.pCommandBuffers = data;
}
