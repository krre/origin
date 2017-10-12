#pragma once
#include "Core/Singleton.h"

namespace Vulkan {
    class Instance;
    class PhysicalDevices;
    class Device;
}

class VulkanCore : public Singleton<VulkanCore> {

public:
    VulkanCore();
    ~VulkanCore();
    Vulkan::Instance* getInstance() const { return instance.get(); }
    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    Vulkan::Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Vulkan::Device* getComputeDevice() const { return computeDevice.get(); }


private:
    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> graphicsDevice;
    std::unique_ptr<Vulkan::Device> computeDevice;
    uint32_t graphicsFamily;
};
