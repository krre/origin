#pragma once
#include "Base/Handle.h"
#include <vector>

#define DEFAULT_FENCE_TIMEOUT 100000000000

namespace Vulkan {

class Device : public Handle<VkDevice> {

public:
    Device(VkPhysicalDevice physicalDevice, uint32_t familyIndex);
    ~Device();
    void waitIdle();
    void waitForFences(uint32_t count, const VkFence* fences);
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
    VkResult create() override;
    void dumpExtensions();

private:
    VkPhysicalDevice physicalDevice;
    VkDeviceCreateInfo createInfo = {};
    VkDeviceQueueCreateInfo queueCreateInfo = {};

    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
    float queuePriority = 1.0f;
};

} // Vulkan
