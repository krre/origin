#pragma once
#include "VulkanObject.h"
#include "Instance.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Surface : public VulkanObject {

public:
    Surface(const Instance* instance);
    bool isValid() const { return handle != 0; }
    VkSurfaceKHR getHandle() const { return handle; }

private:
    const Instance* instance;
    VkSurfaceKHR handle = 0;
};

} // Vulkan
