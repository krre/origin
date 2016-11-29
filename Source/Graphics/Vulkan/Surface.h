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
    Surface(const Instance* instance);
    ~Surface();
    void create() override;

private:
    const Instance* instance;
};

} // Vulkan
