#pragma once
#include "Graphics/Render/RenderWindow.h"
#include <vector>

namespace Vulkan {
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
    void setColorImpl(const Color& color) override;

    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::vector<std::unique_ptr<Vulkan::Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews;
    std::unique_ptr<Vulkan::Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Vulkan::PresentQueue> presentQueue;
    int index = -1;
    static int indexCounter;
};
