#pragma once
#include "../Base/Collection.h"
#include "../Instance.h"
#include "PhysicalDevice.h"
#include <vector>
#include <map>

namespace Vulkan {

class PhysicalDevices : public Collection<VkPhysicalDevice> {

public:
    PhysicalDevices(const Instance* instance);
    VkPhysicalDeviceProperties getProperties(VkPhysicalDevice device) { return properties[device]; }
    VkPhysicalDeviceFeatures getFeatures(VkPhysicalDevice device) { return features[device]; }
    VkPhysicalDeviceMemoryProperties getMemoryProperties(VkPhysicalDevice device) { return memoryProperties[device]; }
    std::vector<VkQueueFamilyProperties> getQueueFamilyProperties(VkPhysicalDevice device) { return queueFamilyProperties[device]; }

    PhysicalDevice* findDevice(VkPhysicalDeviceType type);
    uint32_t findQueue(VkPhysicalDevice device, VkQueueFlags flags);
    uint32_t findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void dumpDevices();

private:
    const Instance* instance;
    std::vector<std::shared_ptr<PhysicalDevice>> devices;
    std::map<VkPhysicalDevice, VkPhysicalDeviceProperties> properties;
    std::map<VkPhysicalDevice, VkPhysicalDeviceFeatures> features;
    std::map<VkPhysicalDevice, VkPhysicalDeviceMemoryProperties> memoryProperties;
    std::map<VkPhysicalDevice, std::vector<VkQueueFamilyProperties>> queueFamilyProperties;
};

} // Vulkan
