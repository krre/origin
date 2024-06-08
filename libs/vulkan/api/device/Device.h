#pragma once
#include "../base/Handle.h"
#include <vector>

namespace Vulkan {

class PhysicalDevice;

class Device : public Handle<VkDevice> {
public:
    Device(PhysicalDevice* physicalDevice);
    ~Device();

    void create() override;
    void destroy() override;

    void waitIdle();
    void waitForFences(std::vector<VkFence> fences);
    void resetFences(std::vector<VkFence> fences);
    PhysicalDevice* physicalDevice() const { return m_physicalDevice; }

    void dumpExtensions();
    void addQueueCreateInfo(uint32_t queueFamilyIndex, std::vector<float> queuePriorities);

private:
    VkDeviceCreateInfo m_createInfo = {};
    PhysicalDevice* m_physicalDevice = nullptr;
    std::vector<VkDeviceQueueCreateInfo> m_queueCreateInfos;
    std::vector<float> m_queuePriorities;
    std::vector<VkExtensionProperties> m_extensions;
    std::vector<const char*> m_enabledExtensions;
};

}
