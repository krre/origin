#pragma once
#include "../Base/Handle.h"
#include <vector>

namespace Vulkan {

class PhysicalDevice : public Handle<VkPhysicalDevice> {
    friend class PhysicalDevices;

public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);
    VkResult create() override {}

    VkPhysicalDeviceProperties& getProperties() { return properties; }
    VkPhysicalDeviceFeatures& getFeatures() { return features; }
    VkPhysicalDeviceMemoryProperties& getMemoryProperties() { return memoryProperties; }
    std::vector<VkQueueFamilyProperties>& getQueueFamilyProperties() { return queueFamilyProperties; }

    uint32_t findQueue(VkQueueFlags flags);

private:
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memoryProperties;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
};

} // Vulkan
