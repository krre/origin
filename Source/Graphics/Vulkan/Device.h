#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device : public VulkanObject {

public:
    Device();
    ~Device();
    bool create();
    VkDevice getDevice() const { return device; }

private:
    VkDevice device = 0;
};

} // Vulkan
