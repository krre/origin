#include "SubmitQueue.h"

using namespace Vulkan;

SubmitQueue::SubmitQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}

VkResult SubmitQueue::submit(VkFence fence) {
    submitInfo.pWaitDstStageMask = waitDstStageMasks.data();
    submitInfo.waitSemaphoreCount = waitSemaphores.size();
    submitInfo.pWaitSemaphores = waitSemaphores.data();
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = signalSemaphores.data();
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = commandBuffers.data();
    CHECK_RESULT(vkQueueSubmit(handle, 1, &submitInfo, fence), "Failed to submit queue");
    return result;
}

VkResult SubmitQueue::waitIdle() {
    return checkError(vkQueueWaitIdle(handle), "Failed to wait idle for queue");
}

void SubmitQueue::addSignalSemaphore(VkSemaphore semaphore) {
    signalSemaphores.push_back(semaphore);
}

void SubmitQueue::addWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags waitDstStageMask) {
    waitSemaphores.push_back(semaphore);
    waitDstStageMasks.push_back(waitDstStageMask);
}

void SubmitQueue::addCommandBuffer(VkCommandBuffer commandBuffer) {
    commandBuffers.push_back(commandBuffer);
}

void SubmitQueue::clearCommandBuffers() {
    commandBuffers.clear();
}
