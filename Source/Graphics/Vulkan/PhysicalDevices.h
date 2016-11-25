#pragma once
#include "VkObject.h"
#include "Instance.h"
#include <vector>

namespace Vulkan {

class PhysicalDevices : public VkObject {

public:
    PhysicalDevices(const Instance* instance);
    uint32_t getCount() const { return count; }
    VkPhysicalDevice getPrimary() const { return primaryDevice; }
    VkPhysicalDevice getSecondary() const { return secondaryDevice; }

private:
    const Instance* instance;
    uint32_t count = 0;
    std::vector<VkPhysicalDevice> devices;
    VkPhysicalDevice primaryDevice = 0;
    VkPhysicalDevice secondaryDevice = 0;
};

} // Vulkan
