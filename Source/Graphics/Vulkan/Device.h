#pragma once
#include "VulkanObject.h"
#include "PhysicalDevice.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device : public VulkanObject {

public:
    Device(const PhysicalDevice* physicalDevice);
    ~Device();
    bool create();
    VkDevice getHandle() const;

private:
    const PhysicalDevice* physicalDevice;
    VkDevice handle = 0;
    VkDeviceCreateInfo createInfo;
};

} // Vulkan
