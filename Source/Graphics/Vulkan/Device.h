#pragma once
#include "VkObject.h"
#include "PhysicalDevices.h"

namespace Vulkan {

class Device : public VkObject {

public:
    Device(VkPhysicalDevice physicalDevice, uint32_t familyIndex);
    ~Device();
    VkDevice getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    void waitIdle();
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }

private:
    VkPhysicalDevice physicalDevice;
    VkDevice handle = VK_NULL_HANDLE;
};

} // Vulkan
