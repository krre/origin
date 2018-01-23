#pragma once
#include <memory>
#include <vector>

namespace Vulkan {

class CommandBuffer;
class CommandBuffers;
class CommandPool;
class Device;
class Framebuffer;
class Image;
class ImageView;
class Instance;
class PhysicalDevices;
class Queue;
class RenderPass;
class Semaphore;
class Semaphore;
class Surface;
class Swapchain;

class Renderer {

public:
    Renderer();
    ~Renderer();

    Vulkan::Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Vulkan::Device* getComputeDevice() const { return computeDevice.get(); }
    Vulkan::CommandPool* getGraphicsCommandPool() const { return graphicsCommandPool.get(); }
    Vulkan::CommandPool* getComputeCommandPool() const { return computeCommandPool.get(); }

    void setEnabledLayers(const std::vector<std::string>& enabledLayers);
    void setEnabledExtensions(const std::vector<std::string>& enabledExtensions);

    void setDeviceIndex(int index) { presetDevice = index; }

    void create();
    void render();
    void resize();
    std::vector<unsigned char> readFramebuffer();

protected:
    void writeCommandBuffers(Vulkan::CommandBuffer* commandBuffer);

private:
    void createAll();

    std::unique_ptr<Vulkan::Instance> instance;
    std::unique_ptr<Vulkan::PhysicalDevices> physicalDevices;
    std::unique_ptr<Vulkan::Device> graphicsDevice;
    std::shared_ptr<Vulkan::CommandPool> graphicsCommandPool;
    std::unique_ptr<Vulkan::Device> computeDevice;
    std::shared_ptr<Vulkan::CommandPool> computeCommandPool;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::vector<std::unique_ptr<Vulkan::Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews;
    std::unique_ptr<Vulkan::Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Vulkan::Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Vulkan::Queue> queue;
    std::unique_ptr<Vulkan::CommandBuffers> commandBufferHandlers;
    std::vector<std::unique_ptr<Vulkan::CommandBuffer>> commandBuffers;
    Vulkan::Device* device;
    uint32_t graphicsFamily;
    uint32_t computeFamily;
    int presetDevice = -1;
};

} // Vulkan
