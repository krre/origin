#include "PresentQueue.h"

using namespace Vulkan;

PresentQueue::PresentQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
}

VkResult PresentQueue::present() {
    assert(swapchains.size() > 0);
    presentInfo.waitSemaphoreCount = waitSemaphores.size();
    presentInfo.pWaitSemaphores = waitSemaphores.data();
    presentInfo.swapchainCount = swapchains.size();
    presentInfo.pSwapchains = swapchains.data();
    presentInfo.pImageIndices = imageIndices.data();
    return checkError(vkQueuePresentKHR(handle, &presentInfo), "Failed to present swapchain image");
}

void PresentQueue::addSwapchain(VkSwapchainKHR swapchain) {
    swapchains.push_back(swapchain);
    imageIndices.push_back(0); // Any uint32_t value
}

uint32_t* PresentQueue::getImageIndex(int i) {
    assert(imageIndices.size() > 0 && i < imageIndices.size());
    return &imageIndices[i];
}
