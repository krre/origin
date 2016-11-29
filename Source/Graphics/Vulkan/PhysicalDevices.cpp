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
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            primaryDevice = device;
        } else {
            secondaryDevice = device;
        }
    }

    if (!primaryDevice) {
        primaryDevice = secondaryDevice;
    }

    if (!secondaryDevice) {
        secondaryDevice = primaryDevice;
    }
}

void PhysicalDevices::dumpDevices() {
    for (auto device: devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        print(deviceProperties.deviceName);
    }
}

