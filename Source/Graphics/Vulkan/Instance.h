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

    uint32_t getLayerCount() const { return layers.size(); }
    VkLayerProperties getLayer(int i) const { return layers.at(i); }
    void dumpLayers();

    uint32_t getExtensionCount() const { return extensions.size(); }
    VkExtensionProperties getExtension(int i) const { return extensions.at(i); }
    void dumpExtensions();

private:
    std::vector<VkLayerProperties> layers;
    std::vector<const char*> enabledLayers;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
};

} // Vulkan
