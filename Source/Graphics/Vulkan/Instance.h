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
class PhysicalDevices;
class Surface;
class CommandPool;

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

    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    Surface* getSurface() const { return surface.get(); }
    CommandPool* getCommandPool() const { return commandPool.get(); }

private:
    void onWindowResize(int width, int height);

    VkInstanceCreateInfo createInfo = {};
    VkApplicationInfo applicationInfo = {};
    std::vector<VkLayerProperties> layers;
    std::vector<const char*> enabledLayers;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
    Device* defaultDevice;
    uint32_t graphicsFamily;
    std::shared_ptr<DebugReportCallback> debugCallback;
    std::shared_ptr<PhysicalDevices> physicalDevices;
    std::vector<std::shared_ptr<Device>> devices;
    std::shared_ptr<Surface> surface;
    std::shared_ptr<CommandPool> commandPool;
};

} // Vulkan
