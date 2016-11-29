#pragma once
#include "VkObject.h"
#include "Instance.h"
#include <vector>
#include <map>

namespace Vulkan {

class PhysicalDevices : public VkObject {

public:
    PhysicalDevices(const Instance* instance);
    uint32_t getCount() const { return devices.size(); }
    VkPhysicalDevice getDevice(size_t i) const { return devices.at(i); }
    VkPhysicalDeviceProperties* getProperties(VkPhysicalDevice device) { return &properties[device]; }
    VkPhysicalDeviceFeatures* getFeatures(VkPhysicalDevice device) { return &features[device]; }
    void dumpDevices();

private:
    const Instance* instance;
    std::vector<VkPhysicalDevice> devices;
    std::map<VkPhysicalDevice, VkPhysicalDeviceProperties> properties;
    std::map<VkPhysicalDevice, VkPhysicalDeviceFeatures> features;
};

} // Vulkan
