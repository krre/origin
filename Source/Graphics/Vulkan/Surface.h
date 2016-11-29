#pragma once
#ifdef __linux__
    #define VK_USE_PLATFORM_XCB_KHR
#elif _WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include "VkCreatableObject.h"
#include "Instance.h"

namespace Vulkan {

class Surface : public VkCreatableObject<VkSurfaceKHR> {

public:
    Surface(const Instance* instance, VkPhysicalDevice physicalDevice);
    ~Surface();
    void create() override;
    int getFormatCount() const { return formats.size(); }
    VkSurfaceFormatKHR getFormat(size_t i) const { return formats.at(i); }

private:
    const Instance* instance;
    VkPhysicalDevice physicalDevice;
    std::vector<VkSurfaceFormatKHR> formats;
};

} // Vulkan
