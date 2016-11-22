#pragma once
#ifdef __linux__
    #define VK_USE_PLATFORM_XCB_KHR
#elif _WIN32
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include "VkObject.h"
#include "Instance.h"

namespace Vulkan {

class Surface : public VkObject {

public:
    Surface(const Instance* instance);
    ~Surface();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkSurfaceKHR getHandle() const { return handle; }

private:
    const Instance* instance;
    VkSurfaceKHR handle = VK_NULL_HANDLE;
};

} // Vulkan
