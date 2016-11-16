#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Queue : public VulkanObject {

public:
    Queue();
    bool isValid() const { return handle != 0; }
    VkQueue getHandle() const { return handle; }

private:
    VkQueue handle = 0;
};

} // Vulkan
