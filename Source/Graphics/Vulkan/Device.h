#pragma once
#include "VkObject.h"
#include "PhysicalDevices.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device : public VkObject {

public:
    Device(const PhysicalDevices* physicalDevices);
    ~Device();
    VkDevice getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    void waitIdle();
    const PhysicalDevices* getPhysicalDevices() const { return physicalDevices; }

private:
    const PhysicalDevices* physicalDevices;
    VkDevice handle = VK_NULL_HANDLE;
};

} // Vulkan
