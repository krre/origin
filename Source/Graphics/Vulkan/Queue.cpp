#include "Queue.h"

using namespace Vulkan;

Queue::Queue(const Device* device) : device(device) {

}

bool Queue::create() {
    // TODO: Set family index and queue index
    vkGetDeviceQueue(device->getHandle(), 0, 0, &handle);
    return true;
}
