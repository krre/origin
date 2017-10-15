#pragma once
#include "Graphics/Render/RenderWindow.h"
#include <vector>

namespace Vulkan {
    class Device;
    class Surface;
    class Swapchain;
    class RenderPass;
    class Image;
    class ImageView;
    class Framebuffer;
    class Semaphore;
    class PresentQueue;
}

class VulkanRenderWindow : public RenderWindow {

public:
    VulkanRenderWindow();

    void clear() override;
    void swapBuffers() override;
    void saveImage(const std::string& filePath) override;

    Vulkan::Surface* getSurface() const { return surface.get(); }
    Vulkan::Swapchain* getSwapchain() const { return swapchain.get(); }
//    Vulkan::RenderPass* getRenderPass() const { return renderPass.get(); }
    void acquireNextImage();
    Vulkan::Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    Vulkan::PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    void rebuild();

private:
    void resize(int width, int height) override;
    void setColorImpl(const Color& color) override;

    Vulkan::Device* device;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::vector<std::unique_ptr<Vulkan::Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews;
    std::unique_ptr<Vulkan::Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Vulkan::PresentQueue> presentQueue;
    uint32_t index = 0; // Game has only one window with index 0
};
