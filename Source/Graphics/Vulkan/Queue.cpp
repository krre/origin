#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device) : device(device) {
    vkGetDeviceQueue(device->getHandle(), 0, 0, &handle);
}
