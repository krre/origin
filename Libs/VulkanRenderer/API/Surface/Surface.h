#pragma once
#include "../Base/Handle.h"
#include <vector>

namespace Vulkan {

class Instance;
class PhysicalDevice;

class Surface : public Handle<VkSurfaceKHR> {

public:
    Surface(Instance* instance, PhysicalDevice* physicalDevice);
    ~Surface();
    void create() override;
    void destroy() override;

    const std::vector<VkSurfaceFormatKHR>& getFormats() const { return formats; }
    const std::vector<VkPresentModeKHR>& getPresentModes() const { return presentModes; }
    const VkSurfaceCapabilitiesKHR& getCapabilities() const { return capabilities; }
    VkExtent2D getCurrentExtent() const;

protected:
    virtual void platformCreateHandle() = 0;
    Instance* instance;

private:
    PhysicalDevice* physicalDevice;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceCapabilitiesKHR capabilities;
};

} // Vulkan
