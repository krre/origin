#pragma once
#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

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
class Surface;
class Swapchain;

class Renderer {

public:
    Renderer(void* platformHandle, void* platformWindow);
    ~Renderer();

    Instance* instance() const { return m_instance.get(); }
    Device* graphicsDevice() const { return m_graphicsDevice.get(); }
    Device* computeDevice() const { return m_computeDevice.get(); }
    CommandPool* graphicsCommandPool() const { return m_graphicsCommandPool.get(); }
    CommandPool* computeCommandPool() const { return m_computeCommandPool.get(); }
    RenderPass* renderPass() const { return m_renderPass.get(); }
    Surface* surface() const { return m_surface.get(); }

    void useDebugReport(VkDebugReportFlagsEXT flags);

    void setEnabledLayers(const std::vector<std::string>& enabledLayers);
    void setEnabledExtensions(const std::vector<std::string>& enabledExtensions);

    void setDeviceIndex(int index) { presetDevice = index; }

    void create();
    void render();
    void resize();
    std::vector<unsigned char> readFramebuffer();

    // Set flag for rebuilding command buffers
    void markDirty() { dirty = true; }

protected:
    virtual void init() {}
    virtual void preRender() {}
    virtual void postRender() {}
    virtual void writeCommandBuffer(CommandBuffer* commandBuffer, Framebuffer* framebuffer) = 0;

private:
    void buildCommandBuffers();

    void* platformHandle;
    void* platformWindow;
    std::unique_ptr<Instance> m_instance;
    std::unique_ptr<PhysicalDevices> physicalDevices;
    std::unique_ptr<Device> m_graphicsDevice;
    std::shared_ptr<CommandPool> m_graphicsCommandPool;
    std::unique_ptr<Device> m_computeDevice;
    std::shared_ptr<CommandPool> m_computeCommandPool;
    std::unique_ptr<Surface> m_surface;
    std::unique_ptr<Swapchain> swapchain;
    std::unique_ptr<RenderPass> m_renderPass;
    std::vector<std::unique_ptr<Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<ImageView>> imageViews;
    std::unique_ptr<Image> depthImage;
    std::unique_ptr<ImageView> depthImageView;
    std::unique_ptr<Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Queue> queue;
    std::unique_ptr<CommandBuffers> commandBuffers;
    uint32_t graphicsFamily;
    uint32_t computeFamily;
    int presetDevice = -1;
    Device* device;
    bool dirty = false;
};

}
