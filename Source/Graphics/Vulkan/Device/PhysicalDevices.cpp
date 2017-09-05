#include "PhysicalDevices.h"
#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(VkInstance instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);
    collection.resize(count);
    vkEnumeratePhysicalDevices(instance, &count, collection.data());

    for (const auto& device : collection) {
        auto physicalDevice = std::make_unique<PhysicalDevice>(device);

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
    for (const auto& device : devices) {
        if (device->properties.deviceType == type) {
            return device.get();
        }
    }

    return nullptr;
}

void PhysicalDevices::dumpDevices() {
    for (const auto& device : devices) {
        PRINT(device->properties.deviceName);
    }
}

