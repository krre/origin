#pragma once
#include "VkCreatableObject.h"
#include <vector>

namespace Vulkan {

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class Instance : public VkCreatableObject<VkInstance> {

public:
    Instance();
    ~Instance();
    bool create() override;
    void destroy() override;

private:
    uint32_t layerCount = 0;
    uint32_t extensionCount = 0;
    std::vector<VkLayerProperties> layers;
    std::vector<VkExtensionProperties> extensions;
};

} // Vulkan
