#pragma once
#include "Base/Handle.h"
#include "DebugReportCallback.h"
#include "../../Core/Singleton.h"
#include <vector>

namespace Vulkan {

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class Device;

class Instance : public Handle<VkInstance>, public Singleton<Instance> {

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

    void setDefaultDevice(Device* device);
    Device* getDefaultDevice() const { return defaultDevice; }

private:
    VkInstanceCreateInfo createInfo = {};
    VkApplicationInfo applicationInfo = {};
    std::vector<VkLayerProperties> layers;
    std::vector<const char*> enabledLayers;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
    Device* defaultDevice;
    std::shared_ptr<DebugReportCallback> debugCallback;
};

} // Vulkan
