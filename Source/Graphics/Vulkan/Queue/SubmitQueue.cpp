#include "SubmitQueue.h"
#include "../Fence.h"
#include "../Semaphore.h"
#include "../Command/CommandBuffer.h"

using namespace Vulkan;

SubmitQueue::SubmitQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}

void SubmitQueue::submit(Fence* fence) {
    append();
    VULKAN_CHECK_RESULT(vkQueueSubmit(handle, submitInfos.size(), submitInfos.data(), fence == nullptr ? VK_NULL_HANDLE : fence->getHandle()), "Failed to submit queue");
}

void SubmitQueue::addSignalSemaphore(Semaphore* semaphore) {
    signalSemaphores.push_back(semaphore->getHandle());
}

void SubmitQueue::addWaitSemaphore(Semaphore* semaphore, VkPipelineStageFlags waitDstStageMask) {
    waitSemaphores.push_back(semaphore->getHandle());
    waitDstStageMasks.push_back(waitDstStageMask);
}

void SubmitQueue::setWaitSemaphore(Semaphore* semaphore, VkPipelineStageFlags waitDstStageMask) {
    waitSemaphores.clear();
    waitDstStageMasks.clear();
    addWaitSemaphore(semaphore, waitDstStageMask);
}

void SubmitQueue::addCommandBuffer(CommandBuffer* commandBuffer) {
    commandBuffers.push_back(commandBuffer->getHandle());
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
