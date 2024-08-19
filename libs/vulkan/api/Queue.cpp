#include "Queue.h"
#include "Semaphore.h"
#include "Fence.h"
#include "command/CommandBuffer.h"
#include "surface/Swapchain.h"

namespace Vulkan {

Queue::Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : Devicer(device) {
    m_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    vkGetDeviceQueue(device->handle(), queueFamilyIndex, queueIndex, &m_handle);
}

void Queue::addPresentWaitSemaphore(VkSemaphore semaphore) {
    m_presentWaitSemaphores.push_back(semaphore);
}

void Queue::clearPresentWaitSemaphores() {
    m_presentWaitSemaphores.clear();
}

void Queue::waitIdle() {
    VULKAN_CHECK_RESULT(vkQueueWaitIdle(m_handle), "Failed to wait idle for queue");
}

void Queue::syncHost(VkFence fence) {
    VULKAN_CHECK_RESULT(vkQueueSubmit(m_handle, 0, nullptr, fence), "Failed to sync host with queue");
}

void Queue::submit(VkFence fence) {
    VULKAN_CHECK_RESULT(vkQueueSubmit(m_handle, m_submitInfos.size(), m_submitInfos.data(), fence), "Failed to submit queue");
}

void Queue::addCommandBuffer(VkCommandBuffer commandBuffer, VkSemaphore signalSemaphore, VkSemaphore waitSemaphore, VkPipelineStageFlags waitDstStageMask) {
    m_commandBuffers.push_back(commandBuffer);

    if (signalSemaphore) {
        m_submitSignalSemaphores.push_back(signalSemaphore);
    }

    if (waitSemaphore) {
        m_submitWaitSemaphores.push_back(waitSemaphore);
        m_submitWaitDstStageMasks.push_back(waitDstStageMask);
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pWaitDstStageMask = m_submitWaitDstStageMasks.data();
    submitInfo.waitSemaphoreCount = m_submitWaitSemaphores.size();
    submitInfo.pWaitSemaphores = m_submitWaitSemaphores.data();
    submitInfo.signalSemaphoreCount = m_submitSignalSemaphores.size();
    submitInfo.pSignalSemaphores = m_submitSignalSemaphores.data();
    submitInfo.commandBufferCount = m_commandBuffers.size();
    submitInfo.pCommandBuffers = m_commandBuffers.data();

    m_submitInfos.push_back(submitInfo);
}

void Queue::clearCommandBuffers() {
    m_commandBuffers.clear();
    m_submitSignalSemaphores.clear();
    m_submitWaitSemaphores.clear();
    m_submitWaitDstStageMasks.clear();
    m_submitInfos.clear();
}

void Queue::present(uint32_t* indices) {
    assert(!m_swapchainHandles.empty());
    m_presentInfo.waitSemaphoreCount = m_presentWaitSemaphores.size();
    m_presentInfo.pWaitSemaphores = m_presentWaitSemaphores.data();
    m_presentInfo.swapchainCount = m_swapchainHandles.size();
    m_presentInfo.pSwapchains = m_swapchainHandles.data();
    m_presentInfo.pImageIndices = indices == nullptr ? m_imageIndices.data() : indices;
    VULKAN_CHECK_RESULT(vkQueuePresentKHR(m_handle, &m_presentInfo), "Failed to present swapchain image");
}

void Queue::addSwapchain(Swapchain* swapchain) {
    m_swapchainHandles.push_back(swapchain->handle());
    m_swapchains.push_back(swapchain);
    m_imageIndices.resize(m_swapchainHandles.size());

    for (int i = 0; i < m_swapchains.size(); i++) {
        m_swapchains.at(i)->setImageIndexPtr(&m_imageIndices.at(i));
    }
}

void Queue::clearSwapchains() {
    m_swapchainHandles.clear();
    m_swapchains.clear();
    m_imageIndices.clear();
}

}
