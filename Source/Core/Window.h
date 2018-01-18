#pragma once
#include "Graphics/Color.h"
#include <string>
#include <vector>
#include <SDL.h>

struct SDL_Window;

namespace Origin {

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

class Screen;

class Window {

public:
    Window();
    ~Window();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

    SDL_Window* getHandle() const { return handle; }

    void pushScreen(const std::shared_ptr<Screen>& screen);
    void popScreen();
    void setScreen(const std::shared_ptr<Screen>& screen);

    void show();
    void update(float dt);
    void render();

    void saveScreenshot();
    void toggleFullScreen();

    void setColor(const Color& color);
    const Color& getColor() const { return color; }

    Vulkan::Surface* getSurface() const { return surface.get(); }
    Vulkan::Swapchain* getSwapchain() const { return swapchain.get(); }
    Vulkan::RenderPass* getRenderPass() const { return renderPass.get(); }
    Vulkan::Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    Vulkan::Semaphore* getRenderFinishedSemaphore() const { return renderFinishedSemaphore.get(); }
    Vulkan::PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    Vulkan::Framebuffer* getFrameBuffer(size_t i) { return framebuffers.at(i).get(); }
    uint32_t getImageIndex() const;

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onMove(int x, int y);
    void onResize(int width, int height);

    SDL_Window* handle = nullptr;
    int x = 0;
    int y = 0;
    uint32_t width = 800;
    uint32_t height = 600;
    std::vector<std::shared_ptr<Screen>> screens;
    Color color = Color(0.9, 1.0, 1.0, 1.0);

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

} // Origin
