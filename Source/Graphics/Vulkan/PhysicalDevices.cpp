#include "PhysicalDevices.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(const Instance* instance) : instance(instance) {
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, nullptr);
    devices.resize(count);
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, devices.data());

    for (auto device: devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        devicesByType[deviceProperties.deviceType] = device;
    }
}

VkPhysicalDevice PhysicalDevices::getPrimary() {
    auto it = devicesByType.find(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    if (it != devicesByType.end()) {
        return it->second;
    } else {
        return devices[0]; // Any first
    }
}

VkPhysicalDevice PhysicalDevices::getSecondary() {
    for (auto it: devicesByType) {
        if (it.first != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            return it.second; // Any not discrete
        }
    }

    return 0;
}
