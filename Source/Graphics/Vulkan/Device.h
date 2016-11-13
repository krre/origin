#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device : public VulkanObject {

public:
    Device();
    ~Device();
    bool create();
    VkDevice getHandle() const;

private:
    VkDevice handle = 0;
};

} // Vulkan
