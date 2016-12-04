#include "SubmitQueue.h"

using namespace Vulkan;

SubmitQueue::SubmitQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}

bool SubmitQueue::submit() {
    return checkError(vkQueueSubmit(handle, 1, &submitInfo, VK_NULL_HANDLE), "Failed to submit draw command buffer");
}

void SubmitQueue::setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores) {
    this->waitSemaphores = waitSemaphores;
    submitInfo.waitSemaphoreCount = waitSemaphores.size();
    submitInfo.pWaitSemaphores = this->waitSemaphores.data();
}

void SubmitQueue::setSignalSemaphores(std::vector<VkSemaphore> signalSemaphores) {
    this->signalSemaphores = signalSemaphores;
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = this->signalSemaphores.data();
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

void SubmitQueue::setCommandBuffersCount(uint32_t count) {
    submitInfo.commandBufferCount = count;
}

void SubmitQueue::setCommandBuffersData(const VkCommandBuffer* data) {
    submitInfo.pCommandBuffers = data;
}
