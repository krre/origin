#pragma once
#include "../Base/Handle.h"
#include <vector>

namespace Vulkan {

class PhysicalDevice : public Handle<VkPhysicalDevice> {
    friend class PhysicalDevices;

public:
    PhysicalDevice(VkPhysicalDevice physicalDevice);
    void create() override {}
    void destroy() override {}

    const VkPhysicalDeviceProperties& getProperties() const { return properties; }
    const VkPhysicalDeviceFeatures& getFeatures() const { return features; }
    const VkPhysicalDeviceMemoryProperties& getMemoryProperties() const { return memoryProperties; }
    const std::vector<VkQueueFamilyProperties>& getQueueFamilyProperties() const { return queueFamilyProperties; }
    VkFormat getSupportedDepthFormat();
    bool getSupportBlit();

    uint32_t findQueue(VkQueueFlags flags);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

private:
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    VkPhysicalDeviceMemoryProperties memoryProperties;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
};

} // Vulkan
