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
class PhysicalDevice;
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

    void setDeviceIndex(int index) { m_presetDevice = index; }

    void create();
    void render();
    void resize();
    std::vector<unsigned char> readFramebuffer();

    // Set flag for rebuilding command buffers
    void markDirty() { m_dirty = true; }

protected:
    virtual void init() {}
    virtual void preRender() {}
    virtual void postRender() {}
    virtual void writeCommandBuffer(CommandBuffer* commandBuffer, Framebuffer* framebuffer) = 0;

private:
    void buildCommandBuffers();
    PhysicalDevice* findDevice(VkPhysicalDeviceType type) const;

    void* m_platformHandle = nullptr;
    void* m_platformWindow = nullptr;
    std::unique_ptr<Instance> m_instance;
    std::vector<std::unique_ptr<PhysicalDevice>> m_physicalDevices;
    std::unique_ptr<Device> m_graphicsDevice;
    std::shared_ptr<CommandPool> m_graphicsCommandPool;
    std::unique_ptr<Device> m_computeDevice;
    std::shared_ptr<CommandPool> m_computeCommandPool;
    std::unique_ptr<Surface> m_surface;
    std::unique_ptr<Swapchain> m_swapchain;
    std::unique_ptr<RenderPass> m_renderPass;
    std::vector<std::unique_ptr<Framebuffer>> m_framebuffers;
    std::vector<std::unique_ptr<ImageView>> m_imageViews;
    std::unique_ptr<Image> m_depthImage;
    std::unique_ptr<ImageView> m_depthImageView;
    std::unique_ptr<Semaphore> m_imageAvailableSemaphore;
    std::unique_ptr<Semaphore> m_renderFinishedSemaphore;
    std::unique_ptr<Queue> m_queue;
    std::unique_ptr<CommandBuffers> m_commandBuffers;
    uint32_t m_graphicsFamily;
    uint32_t m_computeFamily;
    int m_presetDevice = -1;
    Device* m_device = nullptr;
    bool m_dirty = false;
};

}
