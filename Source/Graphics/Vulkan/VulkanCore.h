#pragma once
#include "Core/Singleton.h"

namespace Vulkan {
    class Instance;
    class PhysicalDevices;
    class Device;
    class CommandPool;
    class Surface;
}

class VulkanCore : public Singleton<VulkanCore> {

public:
    VulkanCore();
    ~VulkanCore();
    Vulkan::Instance* getInstance() const { return instance.get(); }
    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    uint32_t getComputeFamily() const { return computeFamily; }
    Vulkan::Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Vulkan::Device* getComputeDevice() const { return computeDevice.get(); }
    Vulkan::CommandPool* getCommandPool() const { return commandPool.get(); }

    void setSurface(Vulkan::Surface* surface) { this->surface = surface; }
    Vulkan::Surface* getSurface() const { return surface; }

private:
    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> graphicsDevice;
    std::unique_ptr<Vulkan::Device> computeDevice;
    std::shared_ptr<Vulkan::CommandPool> commandPool;
    uint32_t graphicsFamily;
    uint32_t computeFamily;
    Vulkan::Surface* surface;
};
