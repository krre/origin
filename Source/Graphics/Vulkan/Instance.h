#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool create();
    VkInstance* getInstance() const { return pInstance; }

private:
    VkInstance* pInstance = nullptr;
    VkInstanceCreateInfo* pCreateInfo = nullptr;
};

} // Vulkan
