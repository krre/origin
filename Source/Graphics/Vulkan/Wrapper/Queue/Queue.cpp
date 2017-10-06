#include "Queue.h"

using namespace Vulkan;

Queue::Queue(uint32_t queueFamilyIndex, uint32_t queueIndex, Device* device) : Devicer(device) {
    vkGetDeviceQueue(this->device->getHandle(), queueFamilyIndex, queueIndex, &handle);
}

void Queue::addWaitSemaphore(VkSemaphore semaphore) {
    waitSemaphores.push_back(semaphore);
}

void Queue::setWaitSemaphore(VkSemaphore semaphore) {
    waitSemaphores.clear();
    addWaitSemaphore(semaphore);
}
