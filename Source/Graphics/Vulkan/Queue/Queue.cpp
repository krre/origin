#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : Devicer(device) {
    vkGetDeviceQueue(device->getHandle(), queueFamilyIndex, queueIndex, &handle);
}

void Queue::addWaitSemaphore(VkSemaphore semaphore) {
    waitSemaphores.push_back(semaphore);
}

void Queue::setWaitSemaphore(VkSemaphore semaphore) {
    waitSemaphores.clear();
    addWaitSemaphore(semaphore);
}
