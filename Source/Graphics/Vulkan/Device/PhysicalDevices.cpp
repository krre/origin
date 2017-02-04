#include "PhysicalDevices.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(const Instance* instance) : instance(instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, nullptr);
    collection.resize(count);
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, collection.data());

    for (auto device : collection) {
        auto physicalDevice = std::make_shared<PhysicalDevice>(device);
        devices.push_back(physicalDevice);

        vkGetPhysicalDeviceProperties(device, &physicalDevice->properties);
        vkGetPhysicalDeviceFeatures(device, &physicalDevice->features);
        vkGetPhysicalDeviceMemoryProperties(device, &physicalDevice->memoryProperties);

        vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
        physicalDevice->queueFamilyProperties.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &count, physicalDevice->queueFamilyProperties.data());
    }
}

PhysicalDevice* PhysicalDevices::findDevice(VkPhysicalDeviceType type) {
    for (auto device : devices) {
        if (device->properties.deviceType == type) {
            return device.get();
        }
    }

    return nullptr;
}

void PhysicalDevices::dumpDevices() {
    for (auto device : devices) {
        PRINT(device->properties.deviceName);
    }
}

