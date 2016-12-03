#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : device(device) {
    vkGetDeviceQueue(device->getHandle(), queueFamilyIndex, queueIndex, &handle);
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
}

void Queue::setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores, bool submit) {
    if (submit) {

    } else {
        this->presentWaitSemaphores = waitSemaphores;
        presentInfo.waitSemaphoreCount = presentWaitSemaphores.size();
        presentInfo.pWaitSemaphores = this->presentWaitSemaphores.data();
    }
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
