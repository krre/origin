#pragma once
#include "Core/Singleton.h"
#include <vector>

namespace Vulkan {

class Instance;
class PhysicalDevices;
class Device;
class CommandPool;

struct ContextProperties {
    std::vector<std::string> layers;
    std::vector<std::string> extensions;
    bool useLayers = false;
    bool useExtensions = false;
    bool dumpLayers = false;
    bool dumpExtensions = false;
};

class Context : public Singleton<Context> {

public:
    Context();
    Context(const ContextProperties& properties);
    ~Context();
    Vulkan::Instance* getInstance() const { return instance.get(); }
    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    uint32_t getComputeFamily() const { return computeFamily; }
    Vulkan::Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Vulkan::Device* getComputeDevice() const { return computeDevice.get(); }
    Vulkan::CommandPool* getGraphicsCommandPool() const { return graphicsCommandPool.get(); }
    Vulkan::CommandPool* getComputeCommandPool() const { return computeCommandPool.get(); }

private:
    void createAll();

    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> graphicsDevice;
    std::shared_ptr<Vulkan::CommandPool> graphicsCommandPool;
    std::unique_ptr<Vulkan::Device> computeDevice;
    std::shared_ptr<Vulkan::CommandPool> computeCommandPool;
    uint32_t graphicsFamily;
    uint32_t computeFamily;
};

} // Vulkan
