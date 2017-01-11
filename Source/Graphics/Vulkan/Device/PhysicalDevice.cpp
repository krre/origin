#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice)  {
    handle = physicalDevice;
}

uint32_t PhysicalDevice::findQueue(VkQueueFlags flags) {
    uint32_t i = 0;
    for (auto familyProperty : queueFamilyProperties) {
        if (familyProperty.queueCount > 0 && (familyProperty.queueFlags & flags)) {
            return i;
        }
        i++;
    }

    return -1;
}
