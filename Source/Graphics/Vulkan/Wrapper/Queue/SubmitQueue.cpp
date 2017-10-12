#include "SubmitQueue.h"

using namespace Vulkan;

SubmitQueue::SubmitQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}

void SubmitQueue::submit(VkFence fence) {
    append();
    VULKAN_CHECK_RESULT(vkQueueSubmit(handle, submitInfos.size(), submitInfos.data(), fence), "Failed to submit queue");
}

void SubmitQueue::waitIdle() {
    VULKAN_CHECK_RESULT(vkQueueWaitIdle(handle), "Failed to wait idle for queue");
}

void SubmitQueue::addSignalSemaphore(VkSemaphore semaphore) {
    signalSemaphores.push_back(semaphore);
}

void SubmitQueue::addWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags waitDstStageMask) {
    waitSemaphores.push_back(semaphore);
    waitDstStageMasks.push_back(waitDstStageMask);
}

void SubmitQueue::setWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags waitDstStageMask) {
    waitSemaphores.clear();
    waitDstStageMasks.clear();
    addWaitSemaphore(semaphore, waitDstStageMask);
}

void SubmitQueue::addCommandBuffer(VkCommandBuffer commandBuffer) {
    commandBuffers.push_back(commandBuffer);
}

void SubmitQueue::clearCommandBuffers() {
    commandBuffers.clear();
}

void SubmitQueue::append() {
    submitInfos.clear();

    submitInfo.pWaitDstStageMask = waitDstStageMasks.data();
    submitInfo.waitSemaphoreCount = waitSemaphores.size();
    submitInfo.pWaitSemaphores = waitSemaphores.data();
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = signalSemaphores.data();
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = commandBuffers.data();

    submitInfos.push_back(submitInfo);
}
