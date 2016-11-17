#pragma once
#include "VulkanObject.h"
#include "PhysicalDevices.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device : public VulkanObject {

public:
    Device(const PhysicalDevices* physicalDevices);
    ~Device();
    VkDevice getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    void waitIdle();

private:
    const PhysicalDevices* physicalDevices;
    VkDevice handle = VK_NULL_HANDLE;
};

} // Vulkan
