#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>
#include <vector>

namespace Vulkan {

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkInstance getHandle() const { return handle; }

private:
    VkInstance handle = VK_NULL_HANDLE;
    uint32_t extensionCount = 0;
    std::vector<VkExtensionProperties> extensions;
};

} // Vulkan
