#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex) : Devicer(device) {
    vkGetDeviceQueue(device->getHandle(), queueFamilyIndex, queueIndex, &handle);
}


