#include "PresentQueue.h"

using namespace Vulkan;

PresentQueue::PresentQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) :
    Queue(device, queueFamilyIndex, queueIndex) {
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
}

VkResult PresentQueue::present() {
    presentInfo.waitSemaphoreCount = waitSemaphores.size();
    presentInfo.pWaitSemaphores = waitSemaphores.data();
    return checkError(vkQueuePresentKHR(handle, &presentInfo), "Failed to present swapchain image");
}

void PresentQueue::setSwapchains(std::vector<VkSwapchainKHR> swapchains) {
    this->swapchains = swapchains;
    presentInfo.swapchainCount = swapchains.size();
    presentInfo.pSwapchains = this->swapchains.data();
}

void PresentQueue::setImageIndices(const uint32_t* indices) {
    presentInfo.pImageIndices = indices;
}
