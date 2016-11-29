#include "PhysicalDevices.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(const Instance* instance) : instance(instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, nullptr);
    devices.resize(count);
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, devices.data());

    for (auto device: devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        properties[device] = deviceProperties;

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        features[device] = deviceFeatures;
    }
}

void PhysicalDevices::dumpDevices() {
    for (auto device: devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        print(deviceProperties.deviceName);
    }
}

