#include "Queue.h"
#include "../Semaphore.h"
#include "../Fence.h"

namespace Origin {

namespace Vulkan {

Queue::Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : Devicer(device) {
    vkGetDeviceQueue(device->getHandle(), queueFamilyIndex, queueIndex, &handle);
}

void Queue::addWaitSemaphore(Semaphore* semaphore) {
    waitSemaphores.push_back(semaphore->getHandle());
}

void Queue::clearWaitSemaphores() {
    waitSemaphores.clear();
}

void Queue::waitIdle() {
    VULKAN_CHECK_RESULT(vkQueueWaitIdle(handle), "Failed to wait idle for queue");
}

void Queue::syncHost(Fence* fence) {
    VULKAN_CHECK_RESULT(vkQueueSubmit(handle, 0, nullptr, fence->getHandle()), "Failed to sync host with queue");
}

} // Vulkan

} // Origin
