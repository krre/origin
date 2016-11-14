#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool isValid() const { return handle != 0; }
    VkInstance getHandle() const { return handle; }

private:
    VkInstance handle = 0;
};

} // Vulkan
