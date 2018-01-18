#pragma once
#include "Graphics/Render/RenderContext.h"

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
    std::shared_ptr<GpuBuffer> createGpuBuffer(GpuBuffer::Usage usage, uint32_t size) override;
    std::shared_ptr<Texture> createTexture(const std::string& path) override;
    std::shared_ptr<ShaderProgram> createShaderProgram(const std::string& name) override;
    std::shared_ptr<RenderState> createRenderState() override;

    Vulkan::Instance* getInstance() const { return instance.get(); }
    uint32_t getGraphicsFamily() const { return graphicsFamily; }
    uint32_t getComputeFamily() const { return computeFamily; }
    Vulkan::Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Vulkan::Device* getComputeDevice() const { return computeDevice.get(); }
    Vulkan::CommandPool* getGraphicsCommandPool() const { return graphicsCommandPool.get(); }
    Vulkan::CommandPool* getComputeCommandPool() const { return computeCommandPool.get(); }

private:
    std::shared_ptr<Renderer> createRenderer() override;
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

#define vkCtx static_cast<VulkanRenderContext*>(RenderContext::get())

} // Origin
