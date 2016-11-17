#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkInstance getHandle() const { return handle; }

private:
    VkInstance handle = VK_NULL_HANDLE;
};

} // Vulkan
