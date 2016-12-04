#pragma once
#include "Base/Handle.h"
#include "PhysicalDevices.h"

namespace Vulkan {

class Device : public Handle<VkDevice> {

public:
    Device(VkPhysicalDevice physicalDevice, uint32_t familyIndex);
    ~Device();
    void waitIdle();
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
    bool create() override;
    void dumpExtensions();

private:
    VkPhysicalDevice physicalDevice;
    VkDeviceCreateInfo createInfo = {};
    VkDeviceQueueCreateInfo queueCreateInfo = {};

    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;

};

} // Vulkan
