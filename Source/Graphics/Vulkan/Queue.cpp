#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device) : device(device) {
    // TODO: Set family index and queue index
    vkGetDeviceQueue(device->getHandle(), 0, 0, &handle);
}
