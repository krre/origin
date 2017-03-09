#pragma once
#include "../Base/Handle.h"
#include "PhysicalDevice.h"
#include <vector>

#define DEFAULT_FENCE_TIMEOUT 100000000000

namespace Vulkan {

class Device : public Handle<VkDevice> {

public:
    Device(PhysicalDevice* physicalDevice, uint32_t familyIndex);
    ~Device();
    void waitIdle();
    void waitForFences(std::vector<VkFence> fences);
    PhysicalDevice* getPhysicalDevice() const { return physicalDevice; }
    VkResult create() override;
    void destroy() override;
    void dumpExtensions();

    VkDeviceCreateInfo createInfo = {};
    VkDeviceQueueCreateInfo queueCreateInfo = {};

private:
    PhysicalDevice* physicalDevice;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
    float queuePriority = 1.0f;
};

} // Vulkan
