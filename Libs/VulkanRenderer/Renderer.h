#pragma once
#include <memory>
#include <vector>

#if defined(_WIN32)
    #include "API/Surface/Win32Surface.h"
#elif defined(__linux__)
    #include "API/Surface/XcbSurface.h"
#endif

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
    struct WindowSettings {
#if defined(_WIN32)
    HINSTANCE hinstance;
    HWND hwnd;
#elif defined(__linux__)
    xcb_connection_t* connection;
    xcb_window_t window;
#endif
    };

    Renderer(WindowSettings windowSettings);
    ~Renderer();

    Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Device* getComputeDevice() const { return computeDevice.get(); }
    CommandPool* getGraphicsCommandPool() const { return graphicsCommandPool.get(); }
    CommandPool* getComputeCommandPool() const { return computeCommandPool.get(); }
    RenderPass* getRenderPass() const { return renderPass.get(); }

    static Renderer* get() { return renderer; }

    void setEnabledLayers(const std::vector<std::string>& enabledLayers);
    void setEnabledExtensions(const std::vector<std::string>& enabledExtensions);

    void setDeviceIndex(int index) { presetDevice = index; }

    void create();
    void render();
    void resize();
    virtual void prepare() = 0;
    std::vector<unsigned char> readFramebuffer();
    void updateCommandBuffers();

protected:
    virtual void init() {}
    virtual void writeCommandBuffers(CommandBuffer* commandBuffer, Framebuffer* framebuffer) = 0;

private:
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
    std::unique_ptr<Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Queue> queue;
    std::unique_ptr<CommandBuffers> commandBufferHandlers;
    std::vector<std::unique_ptr<CommandBuffer>> commandBuffers;
    uint32_t graphicsFamily;
    uint32_t computeFamily;
    int presetDevice = -1;
    Device* device;
    static Renderer* renderer;
    WindowSettings windowSettings;
};

} // Vulkan
