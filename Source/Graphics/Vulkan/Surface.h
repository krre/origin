#pragma once
#ifdef __linux__
    #define VK_USE_PLATFORM_XCB_KHR
#elif _WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include "Base/Handle.h"
#include "Instance.h"

namespace Vulkan {

class Surface : public Handle<VkSurfaceKHR> {

public:
    Surface(VkInstance instance, VkPhysicalDevice physicalDevice);
    ~Surface();
    void create() override;
    void destroy() override;

    const std::vector<VkSurfaceFormatKHR>& getFormats() const { return formats; }
    const std::vector<VkPresentModeKHR>& getPresentModes() const { return presentModes; }
    const VkSurfaceCapabilitiesKHR& getCapabilities() const { return capabilities; }
    VkExtent2D getCurrentExtent() const;

private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceCapabilitiesKHR capabilities;
};

} // Vulkan
