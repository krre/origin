#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevice::PhysicalDevice(const Instance* instance) : instance(instance) {
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, nullptr);
}
