#pragma once
#include "base/Handle.h"
#include <vector>
#include <memory>

namespace Vulkan {

class PhysicalDevice;
class DebugReportCallback;

class Instance : public Handle<VkInstance> {
public:
    Instance();
    ~Instance();

    void create() override;
    void destroy() override;

    const std::vector<VkLayerProperties>& layerProperties() const { return m_layersProperties; }
    void setEnabledLayers(const std::vector<std::string>& enabledLayers);
    void dumpLayers();

    const std::vector<VkExtensionProperties>& extensionProperties() const { return m_extensionProperties; }
    void setEnabledExtensions(const std::vector<std::string>& enabledExtensions);
    void dumpExtensions();

    std::vector<std::unique_ptr<PhysicalDevice>> createPhysicalDevices() const;

    void useDebugReport(VkDebugReportFlagsEXT debugReportFlags) { m_debugReportFlags = debugReportFlags; }

    static std::string apiToString(int api);

private:
    VkInstanceCreateInfo m_createInfo = {};
    VkApplicationInfo m_applicationInfo = {};
    std::vector<VkLayerProperties> m_layersProperties;
    std::vector<std::string> m_enabledLayers;
    std::vector<VkExtensionProperties> m_extensionProperties;
    std::vector<std::string> m_enabledExtensions;
    std::unique_ptr<DebugReportCallback> m_debugCallback;
    VkDebugReportFlagsEXT m_debugReportFlags = 0;
};

}
