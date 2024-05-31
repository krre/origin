#pragma once
#include "../base/Handle.h"
#include <vector>

namespace Vulkan {

class PhysicalDevice;

class Device : public Handle<VkDevice> {

public:
    Device(PhysicalDevice* physicalDevice);
    ~Device();
    void waitIdle();
    void waitForFences(std::vector<VkFence> fences);
    void resetFences(std::vector<VkFence> fences);
    PhysicalDevice* getPhysicalDevice() const { return physicalDevice; }
    void create() override;
    void destroy() override;
    void dumpExtensions();
    void addQueueCreateInfo(uint32_t queueFamilyIndex, std::vector<float> queuePriorities);

private:
    VkDeviceCreateInfo createInfo = {};
    PhysicalDevice* physicalDevice;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::vector<float> queuePriorities;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
};

}
