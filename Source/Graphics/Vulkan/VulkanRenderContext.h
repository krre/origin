#pragma once
#include "Graphics/RenderContext.h"

namespace Origin {

namespace Vulkan {
    class Instance;
    class PhysicalDevices;
    class Device;
    class CommandPool;
}

class VulkanRenderContext : public RenderContext {

public:
    VulkanRenderContext();
    ~VulkanRenderContext();
    RenderWindow* createRenderWindow() override;
    Renderer* createRenderer() override;

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

} // Origin
