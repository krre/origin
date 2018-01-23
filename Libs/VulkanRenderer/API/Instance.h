#pragma once
#include "Base/Handle.h"
#include <vector>
#include <memory>

namespace Vulkan {

class DebugReportCallback;

class Instance : public Handle<VkInstance> {

public:
    Instance();
    ~Instance();

    void create() override;
    void destroy() override;

    const std::vector<VkLayerProperties>& getLayerProperties() const { return layersProperties; }
    void setEnabledLayers(const std::vector<std::string> enabledLayers);
    void dumpLayers();

    const std::vector<VkExtensionProperties>& getExtensionProperties() const { return extensionProperties; }
    void setEnabledExtensions(const std::vector<std::string> enabledExtensions);
    void dumpExtensions();

    void setUseDebugCallback(bool useDebugCallback) { this->useDebugCallback = useDebugCallback; }

    static std::string apiToString(int api);

private:
    VkInstanceCreateInfo createInfo = {};
    VkApplicationInfo applicationInfo = {};
    std::vector<VkLayerProperties> layersProperties;
    std::vector<std::string> enabledLayers;
    std::vector<VkExtensionProperties> extensionProperties;
    std::vector<std::string> enabledExtensions;
    std::unique_ptr<DebugReportCallback> debugCallback;
    bool useDebugCallback = false;
};

} // Vulkan
