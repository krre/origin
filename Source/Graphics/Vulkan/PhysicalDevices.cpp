#include "PhysicalDevices.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(const Instance* instance) : instance(instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, nullptr);
    collection.resize(count);
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, collection.data());

    for (auto device: collection) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        properties[device] = deviceProperties;

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        features[device] = deviceFeatures;

        VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
        vkGetPhysicalDeviceMemoryProperties(device, &deviceMemoryProperties);
        memoryProperties[device] = deviceMemoryProperties;

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

uint32_t PhysicalDevices::findQueue(VkPhysicalDevice device, VkQueueFlags flags) {
    uint32_t i = 0;
    for (auto familyProperty : queueFamilyProperties[device]) {
        if (familyProperty.queueCount > 0 && (familyProperty.queueFlags & flags)) {
            return i;
        }
        i++;

    }

    return -1;
}

uint32_t PhysicalDevices::findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    for (uint32_t i = 0; i < memoryProperties[device].memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memoryProperties[device].memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    return -1;
}

void PhysicalDevices::dumpDevices() {
    for (auto device: collection) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        print(deviceProperties.deviceName);
    }
}

