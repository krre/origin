#pragma once
#include "Core/Singleton.h"
#include "Graphics/Render/RenderState.h"
#include "Graphics/ShaderProgram.h"

namespace Origin {

namespace Vulkan {
    class Instance;
    class PhysicalDevices;
    class Device;
    class CommandPool;
    class Semaphore;
    class Queue;
    class CommandBuffer;
    class CommandBuffers;
    class Surface;
    class Swapchain;
    class RenderPass;
    class Image;
    class ImageView;
    class Framebuffer;
    class Semaphore;
    class Fence;
}

class Window;
class Screen;
class Renderer2D;
class Renderer3D;
class RenderState;
class ShaderProgram;

class RenderEngine : public Singleton<RenderEngine> {

public:
    RenderEngine();
    ~RenderEngine();

    Vulkan::Device* getGraphicsDevice() const { return graphicsDevice.get(); }
    Vulkan::Device* getComputeDevice() const { return computeDevice.get(); }
    Vulkan::CommandPool* getGraphicsCommandPool() const { return graphicsCommandPool.get(); }
    Vulkan::CommandPool* getComputeCommandPool() const { return computeCommandPool.get(); }

    void render(Screen* screen);
    void resizeSwapchain();
    void saveScreenshot();

private:
    void createAll();
    void updateCommandBuffers();

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
    std::unique_ptr<Vulkan::Fence> presentFence;
    std::unique_ptr<Vulkan::Queue> queue;
    std::unique_ptr<Vulkan::CommandBuffers> commandBufferHandlers;
    std::vector<std::unique_ptr<Vulkan::CommandBuffer>> commandBuffers;
    Vulkan::Device* device;
    uint32_t graphicsFamily;
    uint32_t computeFamily;

    void createRenderStates();
    void createShaderPrograms();

    std::unique_ptr<Renderer2D> renderer2d;
    std::unique_ptr<Renderer3D> renderer3d;

    std::map<ShaderProgram::ProgamType, std::shared_ptr<ShaderProgram>> shaderPrograms;
    std::map<RenderState::Type, std::shared_ptr<RenderState>> renderStates;

    Window* window = nullptr;
};

} // Origin
