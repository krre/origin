#include "PhysicalDevices.h"
#include "PhysicalDevice.h"
#include "../Instance.h"

using namespace Vulkan;

PhysicalDevices::PhysicalDevices(Instance* instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, nullptr);
    std::vector<VkPhysicalDevice> handlers(count);
    vkEnumeratePhysicalDevices(instance->getHandle(), &count, handlers.data());

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
