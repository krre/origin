#pragma once
#include "../Base/Handle.h"
#include <vector>

namespace Vulkan {

class PhysicalDevice : public Handle<VkPhysicalDevice> {
    friend class PhysicalDevices;

public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);
    VkResult create() override {}

private:
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
};

} // Vulkan
