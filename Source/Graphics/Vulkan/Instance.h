#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    VkInstance getHandle() const { return handle; }

private:
    VkInstance handle = 0;
};

} // Vulkan
