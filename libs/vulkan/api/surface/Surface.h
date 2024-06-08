#pragma once
#include "../base/Handle.h"
#include <vector>

namespace Vulkan {

class Instance;
class PhysicalDevice;

class Surface : public Handle<VkSurfaceKHR> {
public:
    Surface(Instance* instance, PhysicalDevice* physicalDevice, void* platformHandle, void* platformWindow);
    ~Surface();

    void create() override;
    void destroy() override;

    const std::vector<VkSurfaceFormatKHR>& formats() const { return m_formats; }
    const std::vector<VkPresentModeKHR>& presentModes() const { return m_presentModes; }
    const VkSurfaceCapabilitiesKHR& capabilities() const { return m_capabilities; }
    VkExtent2D currentExtent() const;

private:
    Instance* m_instance = nullptr;
    PhysicalDevice* m_physicalDevice = nullptr;
    void* m_platformHandle = nullptr;
    void* m_platformWindow = nullptr;
    std::vector<VkSurfaceFormatKHR> m_formats;
    std::vector<VkPresentModeKHR> m_presentModes;
    VkSurfaceCapabilitiesKHR m_capabilities;
};

}
