#pragma once
#include "VkObject.h"
#include "Instance.h"
#include <vector>

namespace Vulkan {

class PhysicalDevices : public VkObject {

public:
    PhysicalDevices(const Instance* instance);
    uint32_t getCount() const { return devices.size(); }
    VkPhysicalDevice getDevice(size_t i) const { return devices.at(i); }
    void dumpDevices();
    VkPhysicalDevice getPrimary() const { return primaryDevice; }
    VkPhysicalDevice getSecondary() const { return secondaryDevice; }

private:
    const Instance* instance;
    std::vector<VkPhysicalDevice> devices;
    VkPhysicalDevice primaryDevice = 0;
    VkPhysicalDevice secondaryDevice = 0;
};

} // Vulkan
