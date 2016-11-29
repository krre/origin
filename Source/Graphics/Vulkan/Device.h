#pragma once
#include "VkCreatableObject.h"
#include "PhysicalDevices.h"

namespace Vulkan {

class Device : public VkCreatableObject<VkDevice> {

public:
    Device(VkPhysicalDevice physicalDevice, uint32_t familyIndex);
    ~Device();
    void waitIdle();
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
    void create() override;

private:
    VkPhysicalDevice physicalDevice;
    VkDeviceCreateInfo createInfo;
};

} // Vulkan
