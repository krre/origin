#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Surface : public VulkanObject {

public:
    Surface();
    bool isValid() const { return handle != 0; }
    VkSurfaceKHR getHandle() const { return handle; }

private:
   VkSurfaceKHR handle = 0;
};

} // Vulkan
