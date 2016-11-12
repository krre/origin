#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool create();
    VkInstance* getInstance() const { return instance; }

private:
    VkInstance* instance = nullptr;
    VkInstanceCreateInfo createInfo;
};

} // Vulkan
