#include "PresentQueue.h"
#include "../Surface/Swapchain.h"

using namespace Vulkan;

PresentQueue::PresentQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
}

void PresentQueue::present() {
    assert(!swapchainHandles.empty());
    presentInfo.waitSemaphoreCount = waitSemaphores.size();
    presentInfo.pWaitSemaphores = waitSemaphores.data();
    presentInfo.swapchainCount = swapchainHandles.size();
    presentInfo.pSwapchains = swapchainHandles.data();
    presentInfo.pImageIndices = imageIndices.data();
    VULKAN_CHECK_RESULT(vkQueuePresentKHR(handle, &presentInfo), "Failed to present swapchain image");
}

void PresentQueue::addSwapchain(Swapchain* swapchain) {
    swapchainHandles.push_back(swapchain->getHandle());
    swapchains.push_back(swapchain);
    imageIndices.resize(swapchainHandles.size());

    for (int i = 0; i < swapchains.size(); i++) {
        swapchains.at(i)->setImageIndexPtr(&imageIndices.at(i));
    }
}

void PresentQueue::clearSwapchains() {
    swapchainHandles.clear();
    swapchains.clear();
    imageIndices.clear();
}
