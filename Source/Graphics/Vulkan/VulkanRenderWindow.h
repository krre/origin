#pragma once
#include "Graphics/Render/RenderWindow.h"

namespace Vulkan {
    class Device;
    class Surface;
    class Swapchain;
    class RenderPass;
    class Image;
    class ImageView;
    class Framebuffer;
    class Semaphore;
    class Fence;
    class PresentQueue;
}

class VulkanRenderWindow : public RenderWindow {

public:
    VulkanRenderWindow();
    ~VulkanRenderWindow();
    void render() override;

    Vulkan::Surface* getSurface() const { return surface.get(); }
    Vulkan::Swapchain* getSwapchain() const { return swapchain.get(); }
    Vulkan::RenderPass* getRenderPass() const { return renderPass.get(); }
    Vulkan::Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    Vulkan::PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    Vulkan::Framebuffer* getFrameBuffer(size_t i) { return framebuffers.at(i).get(); }

private:
    void onResize(int width, int height) override;
    void saveScreenshotImpl(const std::string& filePath) override;
    Uint32 getSurfaceFlag() const override;

    Vulkan::Device* device;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::vector<std::unique_ptr<Vulkan::Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews;
    std::unique_ptr<Vulkan::Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Vulkan::Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Vulkan::PresentQueue> presentQueue;
    std::unique_ptr<Vulkan::Fence> presentFence;
};
