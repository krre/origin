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
    VkResult create() override;
    void destroy() override;

    uint32_t getWidth() const { return capabilities.currentExtent.width; }
    uint32_t getHeight() const { return capabilities.currentExtent.height; }

    int getFormatCount() const { return formats.size(); }
    const VkSurfaceFormatKHR& getFormat(size_t i) const { return formats.at(i); }

    int getPresentModeCount() const { return presentModes.size(); }
    const VkPresentModeKHR& getPresentMode(size_t i) const { return presentModes.at(i); }

    const VkSurfaceCapabilitiesKHR& getCapabilities() const { return capabilities; }

private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceCapabilitiesKHR capabilities;
};

} // Vulkan
