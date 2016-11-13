#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool create();
    VkInstance getHandle() const;

private:
    VkInstance handle = 0;
    VkApplicationInfo appInfo;
    VkInstanceCreateInfo createInfo;
};

} // Vulkan
