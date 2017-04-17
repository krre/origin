#include "PhysicalDevices.h"
#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(VkInstance instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);
    collection.resize(count);
    vkEnumeratePhysicalDevices(instance, &count, collection.data());

    for (auto& device : collection) {
        std::unique_ptr<PhysicalDevice> physicalDevice = std::unique_ptr<PhysicalDevice>(new PhysicalDevice(device));

        vkGetPhysicalDeviceProperties(device, &physicalDevice->properties);
        vkGetPhysicalDeviceFeatures(device, &physicalDevice->features);
        vkGetPhysicalDeviceMemoryProperties(device, &physicalDevice->memoryProperties);

        vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
        physicalDevice->queueFamilyProperties.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &count, physicalDevice->queueFamilyProperties.data());

        devices.push_back(std::move(physicalDevice));
    }
}

PhysicalDevice* PhysicalDevices::findDevice(VkPhysicalDeviceType type) {
    for (auto& device : devices) {
        if (device->properties.deviceType == type) {
            return device.get();
        }
    }

    return nullptr;
}

void PhysicalDevices::dumpDevices() {
    for (auto& device : devices) {
        PRINT(device->properties.deviceName);
    }
}

