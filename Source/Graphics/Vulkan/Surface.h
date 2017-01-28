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
    Surface(const Instance* instance, VkPhysicalDevice physicalDevice);
    ~Surface();
    VkResult create() override;
    void destroy() override;

    int getFormatCount() const { return formats.size(); }
    VkSurfaceFormatKHR getFormat(size_t i) const { return formats.at(i); }

    int getPresentModeCount() const { return presentModes.size(); }
    VkPresentModeKHR getPresentMode(size_t i) const { return presentModes.at(i); }

    VkSurfaceCapabilitiesKHR getCapabilities() const { return capabilities; }

private:
    const Instance* instance;
    VkPhysicalDevice physicalDevice;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    VkSurfaceCapabilitiesKHR capabilities;
};

} // Vulkan
