#pragma once
#include "VkCreatableObject.h"
#include <vector>

#undef ASSERT_ERROR

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
    void create() override;
    uint32_t getLayerCount() const { return layerCount; }
    void dumpLayers();

private:
    uint32_t layerCount = 0;
    uint32_t extensionCount = 0;
    std::vector<VkLayerProperties> layers;
    std::vector<VkExtensionProperties> extensions;
};

} // Vulkan
