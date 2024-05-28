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

    const std::vector<VkSurfaceFormatKHR>& getFormats() const { return formats; }
    const std::vector<VkPresentModeKHR>& getPresentModes() const { return presentModes; }
    const VkSurfaceCapabilitiesKHR& getCapabilities() const { return capabilities; }
    VkExtent2D getCurrentExtent() const;

private:
    Instance* instance;
    PhysicalDevice* physicalDevice;
    void* platformHandle;
    void* platformWindow;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceCapabilitiesKHR capabilities;
};

} // Vulkan
