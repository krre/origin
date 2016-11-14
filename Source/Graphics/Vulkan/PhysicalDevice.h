#pragma once
#include "VulkanObject.h"
#include "Instance.h"
#include <vulkan/vulkan.h>
#include <vector>
#include <map>

namespace Vulkan {

class PhysicalDevice : public VulkanObject {

public:
    PhysicalDevice(const Instance* instance);
    uint32_t getCount() const { return count; }
    VkPhysicalDevice getPrimary();
    VkPhysicalDevice getSecondary();

private:
    const Instance* instance;
    uint32_t count = 0;
    std::vector<VkPhysicalDevice> devices;
    std::map<VkPhysicalDeviceType, VkPhysicalDevice> devicesByType;
};

} // Vulkan
