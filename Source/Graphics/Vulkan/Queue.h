#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Queue : public VulkanObject {

public:
    Queue();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkQueue getHandle() const { return handle; }

private:
    VkQueue handle = VK_NULL_HANDLE;
};

} // Vulkan
