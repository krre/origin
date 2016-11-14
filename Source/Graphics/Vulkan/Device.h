#pragma once
#include "VulkanObject.h"
#include "PhysicalDevices.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device : public VulkanObject {

public:
    Device(const PhysicalDevices* physicalDevices);
    ~Device();
    bool create();
    VkDevice getHandle() const;

private:
    const PhysicalDevices* physicalDevices;
    VkDevice handle = 0;
    VkDeviceCreateInfo createInfo;
};

} // Vulkan
