#pragma once
#include "VulkanObject.h"
#include <vulkan/vulkan.h>
#include <vector>

namespace Vulkan {

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class Instance : public VulkanObject {

public:
    Instance();
    ~Instance();
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkInstance getHandle() const { return handle; }

private:
    VkInstance handle = VK_NULL_HANDLE;
    uint32_t layerCount = 0;
    uint32_t extensionCount = 0;
    std::vector<VkLayerProperties> layers;
    std::vector<VkExtensionProperties> extensions;
};

} // Vulkan
