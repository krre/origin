#include "Queue.h"
#include "../Semaphore.h"

using namespace Vulkan;

Queue::Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : Devicer(device) {
    vkGetDeviceQueue(device->getHandle(), queueFamilyIndex, queueIndex, &handle);
}

void Queue::addWaitSemaphore(Semaphore* semaphore) {
    waitSemaphores.push_back(semaphore->getHandle());
}
