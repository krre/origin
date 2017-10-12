#pragma once
#include "Base/Handle.h"
#include <vector>

class RenderWindow;

namespace Vulkan {

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class DebugReportCallback;
class Surface;

class Instance : public Handle<VkInstance> {

public:
    Instance();
    ~Instance();

    void create() override;
    void destroy() override;

    const std::vector<VkLayerProperties>& getLayers() const { return layers; }
    void setEnabledLayers(const std::vector<const char*> enabledLayers);
    void dumpLayers();

    const std::vector<VkExtensionProperties>& getExtensions() const { return extensions; }
    void setEnabledExtensions(const std::vector<const char*> enabledExtensions);
    void dumpExtensions();

    void setSurface(Surface* surface) { this->surface = surface; }
    Surface* getSurface() const { return surface; }

    void windowResize(int width, int height);

    static std::string apiToString(int api);

private:
    VkInstanceCreateInfo createInfo = {};
    VkApplicationInfo applicationInfo = {};
    std::vector<VkLayerProperties> layers;
    std::vector<const char*> enabledLayers;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
    std::unique_ptr<DebugReportCallback> debugCallback;
    Surface* surface;
};

} // Vulkan
