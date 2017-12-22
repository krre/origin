#include "SubmitQueue.h"
#include "../Fence.h"
#include "../Semaphore.h"
#include "../Command/CommandBuffer.h"

using namespace Vulkan;

SubmitQueue::SubmitQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
}

void SubmitQueue::submit(Fence* fence) {
    VULKAN_CHECK_RESULT(vkQueueSubmit(handle, submitInfos.size(), submitInfos.data(), fence == nullptr ? VK_NULL_HANDLE : fence->getHandle()), "Failed to submit queue");
}

void SubmitQueue::addCommandBuffer(CommandBuffer* commandBuffer, Semaphore* waitSemaphore, VkPipelineStageFlags waitDstStageMask, Semaphore* signalSemaphore) {
    commandBuffers.push_back(commandBuffer->getHandle());
    signalSemaphores.push_back(signalSemaphore->getHandle());
    waitSemaphores.push_back(waitSemaphore->getHandle());
    waitDstStageMasks.push_back(waitDstStageMask);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pWaitDstStageMask = waitDstStageMasks.data();
    submitInfo.waitSemaphoreCount = waitSemaphores.size();
    submitInfo.pWaitSemaphores = waitSemaphores.data();
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = signalSemaphores.data();
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = commandBuffers.data();

    submitInfos.push_back(submitInfo);
}

void SubmitQueue::addCommandBuffer(CommandBuffer* commandBuffer, Semaphore* signalSemaphore) {
    commandBuffers.push_back(commandBuffer->getHandle());
    signalSemaphores.push_back(signalSemaphore->getHandle());

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = commandBuffers.data();
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = signalSemaphores.data();

    submitInfos.push_back(submitInfo);
}

void SubmitQueue::addCommandBuffer(CommandBuffer* commandBuffer) {
    commandBuffers.push_back(commandBuffer->getHandle());

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = commandBuffers.data();

    submitInfos.push_back(submitInfo);
}

void SubmitQueue::clearCommandBuffers() {
    commandBuffers.clear();
    signalSemaphores.clear();
    waitSemaphores.clear();
    waitDstStageMasks.clear();
    submitInfos.clear();
}
