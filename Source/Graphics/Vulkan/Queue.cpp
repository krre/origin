#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device) : device(device) {

}

void Queue::create() {
    // TODO: Set family index and queue index
    vkGetDeviceQueue(device->getHandle(), 0, 0, &handle);
}
