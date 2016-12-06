#include "PhysicalDeviceCollection.h"

using namespace Vulkan;

PhysicalDeviceCollection::PhysicalDeviceCollection(const Instance* instance) : instance(instance) {
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

VkPhysicalDevice PhysicalDeviceCollection::findDevice(VkPhysicalDeviceType type) {
    for (auto device : properties) {
        if (device.second.deviceType == type) {
            return device.first;
        }
    }

    return VK_NULL_HANDLE;
}

uint32_t PhysicalDeviceCollection::findQueue(VkPhysicalDevice device, VkQueueFlags flags) {
    uint32_t i = 0;
    for (auto familyProperty : queueFamilyProperties[device]) {
        if (familyProperty.queueCount > 0 && (familyProperty.queueFlags & flags)) {
            return i;
        }
        i++;

    }

    return -1;
}

void PhysicalDeviceCollection::dumpDevices() {
    for (auto device: collection) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        print(deviceProperties.deviceName);
    }
}

