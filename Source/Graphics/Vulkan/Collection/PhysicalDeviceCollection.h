#pragma once
#include "../Base/Collection.h"
#include "../Instance.h"
#include <vector>
#include <map>

namespace Vulkan {

class PhysicalDeviceCollection : public Collection<VkPhysicalDevice> {

public:
    PhysicalDeviceCollection(const Instance* instance);
    VkPhysicalDeviceProperties getProperties(VkPhysicalDevice device) { return properties[device]; }
    VkPhysicalDeviceFeatures getFeatures(VkPhysicalDevice device) { return features[device]; }
    std::vector<VkQueueFamilyProperties> getQueueFamilyProperties(VkPhysicalDevice device) { return queueFamilyProperties[device]; }
    VkPhysicalDevice findDevice(VkPhysicalDeviceType type);
    uint32_t findQueue(VkPhysicalDevice device, VkQueueFlags flags);
    void dumpDevices();

private:
    const Instance* instance;
    std::map<VkPhysicalDevice, VkPhysicalDeviceProperties> properties;
    std::map<VkPhysicalDevice, VkPhysicalDeviceFeatures> features;
    std::map<VkPhysicalDevice, std::vector<VkQueueFamilyProperties>> queueFamilyProperties;
};

} // Vulkan
