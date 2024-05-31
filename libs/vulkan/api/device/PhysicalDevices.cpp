#include "PhysicalDevices.h"
#include "PhysicalDevice.h"
#include "../Instance.h"
#include <iostream>

namespace Vulkan {

PhysicalDevices::PhysicalDevices(Instance* instance) {
    uint32_t count;
    vkEnumeratePhysicalDevices(instance->handle(), &count, nullptr);
    std::vector<VkPhysicalDevice> handlers(count);
    vkEnumeratePhysicalDevices(instance->handle(), &count, handlers.data());

    for (const auto& handler : handlers) {
        auto physicalDevice = std::make_unique<PhysicalDevice>(handler);

        vkGetPhysicalDeviceProperties(handler, &physicalDevice->m_properties);
        vkGetPhysicalDeviceFeatures(handler, &physicalDevice->m_features);
        vkGetPhysicalDeviceMemoryProperties(handler, &physicalDevice->m_memoryProperties);

        vkGetPhysicalDeviceQueueFamilyProperties(handler, &count, nullptr);
        physicalDevice->m_queueFamilyProperties.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(handler, &count, physicalDevice->m_queueFamilyProperties.data());

        devices.push_back(std::move(physicalDevice));
    }
}

PhysicalDevice* PhysicalDevices::findDevice(VkPhysicalDeviceType type) {
    for (const auto& device : devices) {
        if (device->m_properties.deviceType == type) {
            return device.get();
        }
    }

    return nullptr;
}

void PhysicalDevices::dumpDevices() {
    for (const auto& device : devices) {
        std::cout << device->m_properties.deviceName << std::endl;
    }
}

}
