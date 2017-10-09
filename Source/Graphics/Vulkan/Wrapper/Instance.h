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

class Device;
class PhysicalDevices;
class CommandPool;
class DebugReportCallback;
class Surface;

class Instance : public Handle<VkInstance> {

public:
    Instance();
    ~Instance();
    static Instance* get() { return instance; }

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

    void setSurface(Surface* surface) { this->surface = surface; }
    Surface* getSurface() const { return surface; }

    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    CommandPool* getCommandPool() const { return commandPool.get(); }

    void windowResize(int width, int height);

    static std::string apiToString(int api);

private:
    static Instance* instance;
    VkInstanceCreateInfo createInfo = {};
    VkApplicationInfo applicationInfo = {};
    std::vector<VkLayerProperties> layers;
    std::vector<const char*> enabledLayers;
    std::vector<VkExtensionProperties> extensions;
    std::vector<const char*> enabledExtensions;
    Device* defaultDevice;
    uint32_t graphicsFamily;
    std::unique_ptr<DebugReportCallback> debugCallback;
    std::shared_ptr<PhysicalDevices> physicalDevices;
    std::vector<std::shared_ptr<Device>> devices;
    std::shared_ptr<CommandPool> commandPool;
    Surface* surface;
};

} // Vulkan
