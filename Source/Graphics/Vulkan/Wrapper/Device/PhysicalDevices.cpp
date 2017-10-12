#include "PhysicalDevices.h"
#include "PhysicalDevice.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(VkInstance instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);
    std::vector<VkPhysicalDevice> handlers(count);
    vkEnumeratePhysicalDevices(instance, &count, handlers.data());

    for (const auto& handler : handlers) {
        auto physicalDevice = std::make_unique<PhysicalDevice>(handler);

        vkGetPhysicalDeviceProperties(handler, &physicalDevice->properties);
        vkGetPhysicalDeviceFeatures(handler, &physicalDevice->features);
        vkGetPhysicalDeviceMemoryProperties(handler, &physicalDevice->memoryProperties);

        vkGetPhysicalDeviceQueueFamilyProperties(handler, &count, nullptr);
        physicalDevice->queueFamilyProperties.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(handler, &count, physicalDevice->queueFamilyProperties.data());

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
