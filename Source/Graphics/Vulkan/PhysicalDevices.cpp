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

        vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
        std::vector<VkQueueFamilyProperties> familyProperties(count);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &count, familyProperties.data());
        queueFamilyProperties[device] = familyProperties;
    }
}

VkPhysicalDevice PhysicalDevices::findDevice(VkPhysicalDeviceType type) {
    for (auto device : properties) {
        if (device.second.deviceType == type) {
            return device.first;
        }
    }

    return VK_NULL_HANDLE;
}

int PhysicalDevices::findQueue(VkPhysicalDevice device, VkQueueFlags flags) {
    int i = 0;
    for (auto familyProperty : queueFamilyProperties[device]) {
        if (familyProperty.queueCount > 0 && (familyProperty.queueFlags & flags)) {
            return i;
        }
        i++;

    }

    return -1;
}

void PhysicalDevices::dumpDevices() {
    for (auto device: devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        print(deviceProperties.deviceName);
    }
}

