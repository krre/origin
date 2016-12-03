#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : device(device) {
    vkGetDeviceQueue(device->getHandle(), queueFamilyIndex, queueIndex, &handle);
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
}

void Queue::setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores, bool submit) {
    if (submit) {
        this->submitWaitSemaphores = waitSemaphores;
        submitInfo.waitSemaphoreCount = submitWaitSemaphores.size();
        submitInfo.pWaitSemaphores = this->submitWaitSemaphores.data();
    } else {
        this->presentWaitSemaphores = waitSemaphores;
        presentInfo.waitSemaphoreCount = presentWaitSemaphores.size();
        presentInfo.pWaitSemaphores = this->presentWaitSemaphores.data();
    }
}

void Queue::setSignalSemaphores(std::vector<VkSemaphore> signalSemaphores) {
    this->signalSemaphores = signalSemaphores;
    submitInfo.signalSemaphoreCount = signalSemaphores.size();
    submitInfo.pSignalSemaphores = this->signalSemaphores.data();
}

void Queue::setWaitDstStageMask(std::vector<VkPipelineStageFlags> waitDstStageMask) {
    this->waitDstStageMask = waitDstStageMask;
    submitInfo.pWaitDstStageMask = this->waitDstStageMask.data();
}

void Queue::setCommandBuffers(std::vector<VkCommandBuffer> commandBuffers) {
    this->commandBuffers = commandBuffers;
    submitInfo.commandBufferCount = commandBuffers.size();
    submitInfo.pCommandBuffers = this->commandBuffers.data();
}

void Queue::setCommandBuffersCount(uint32_t count) {
    submitInfo.commandBufferCount = count;
}

void Queue::setCommandBuffersData(const VkCommandBuffer* data) {
    submitInfo.pCommandBuffers = data;
}

bool Queue::submit() {
    return checkError(vkQueueSubmit(handle, 1, &submitInfo, VK_NULL_HANDLE), "Failed to submit draw command buffer");
}

bool Queue::present() {
    return checkError(vkQueuePresentKHR(handle, &presentInfo), "Failed to present swapchain image");
}

void Queue::setSwapchains(std::vector<VkSwapchainKHR> swapchains) {
    this->swapchains = swapchains;
    presentInfo.swapchainCount = swapchains.size();
    presentInfo.pSwapchains = this->swapchains.data();
}

void Queue::setImageIndices(const uint32_t* indices) {
    presentInfo.pImageIndices = indices;
}
