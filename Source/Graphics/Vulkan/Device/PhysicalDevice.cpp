#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice)  {
    handle = physicalDevice;
}

