#pragma once
#include "Graphics/Render/RenderTarget.h"
#include "Graphics/Color.h"
#include <string>
#include <vector>

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

struct SDL_Window;

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

class RenderWindow : public RenderTarget {

public:
    RenderWindow();
    ~RenderWindow();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }

    void show();

    void acquireNextImage();
    void present();

    void saveImage(const std::string& filePath);

    Vulkan::Surface* getSurface() const { return surface.get(); }
    Vulkan::Swapchain* getSwapchain() const { return swapchain.get(); }
//    Vulkan::RenderPass* getRenderPass() const { return renderPass.get(); }
    Vulkan::Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    Vulkan::PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    void rebuild();

    SDL_Window* getHandle() { return handle; }

protected:

private:
    void onMove(int x, int y);
    void onResize(int width, int height);

    Vulkan::Device* device;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::vector<std::unique_ptr<Vulkan::Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews;
    std::unique_ptr<Vulkan::Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Vulkan::PresentQueue> presentQueue;
    uint32_t index = 0; // Game has only one window with index 0

    SDL_Window* handle = nullptr;
    int x = 100;
    int y = 100;
};
