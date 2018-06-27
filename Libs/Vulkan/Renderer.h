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
class Surface;
class Swapchain;

class Renderer {

public:
    Renderer(void* platformHandle, void* platformWindow);
    ~Renderer();

    Instance* getInstance() const { return instance.get(); }
    Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Device* getComputeDevice() const { return computeDevice.get(); }
    CommandPool* getGraphicsCommandPool() const { return graphicsCommandPool.get(); }
    CommandPool* getComputeCommandPool() const { return computeCommandPool.get(); }
    RenderPass* getRenderPass() const { return renderPass.get(); }
    Surface* getSurface() const { return surface.get(); }

    void useDebugMessages();
    void setEnabledLayers(const std::vector<std::string>& enabledLayers);
    void setEnabledExtensions(const std::vector<std::string>& enabledExtensions);

    void setDeviceIndex(int index) { presetDevice = index; }

    void create();
    void render();
    void resize();
    std::vector<unsigned char> readFramebuffer();
    void updateCommandBuffers();

protected:
    virtual void init() {}
    virtual void preRender() {}
    virtual void postRender() {}
    virtual void writeCommandBuffers(CommandBuffer* commandBuffer, Framebuffer* framebuffer) = 0;

private:
    void* platformHandle;
    void* platformWindow;
    std::unique_ptr<Instance> instance;
    std::unique_ptr<PhysicalDevices> physicalDevices;
    std::unique_ptr<Device> graphicsDevice;
    std::shared_ptr<CommandPool> graphicsCommandPool;
    std::unique_ptr<Device> computeDevice;
    std::shared_ptr<CommandPool> computeCommandPool;
    std::unique_ptr<Surface> surface;
    std::unique_ptr<Swapchain> swapchain;
    std::unique_ptr<RenderPass> renderPass;
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
};

} // Vulkan
