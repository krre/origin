#pragma once
#include "Graphics/Render/RenderTarget.h"
#include "Graphics/Color.h"
#include <string>
#include <vector>
#include <SDL.h>

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

struct SDL_Window;
class Screen;

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
    class SubmitQueue;
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

    void pushScreen(const std::shared_ptr<Screen>& screen);
    void popScreen();
    void setScreen(const std::shared_ptr<Screen>& screen);

    void show();

    void update(float dt);
    void render();

    void saveScreenshot();
    void toggleFullScreen();

    Vulkan::Surface* getSurface() const { return surface.get(); }
    Vulkan::Swapchain* getSwapchain() const { return swapchain.get(); }
    Vulkan::RenderPass* getRenderPass() const { return renderPass.get(); }
    Vulkan::Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    Vulkan::PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    Vulkan::Framebuffer* getFrameBuffer(size_t i) { return framebuffers.at(i).get(); }

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void onMove(int x, int y);
    void onResize(int width, int height);

    Vulkan::Device* device;
    std::unique_ptr<Vulkan::Surface> surface;
    std::unique_ptr<Vulkan::Swapchain> swapchain;
    std::unique_ptr<Vulkan::RenderPass> renderPass;
    std::vector<std::unique_ptr<Vulkan::Framebuffer>> framebuffers;
    std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews;
    std::unique_ptr<Vulkan::Semaphore> imageAvailableSemaphore;
    std::unique_ptr<Vulkan::Semaphore> renderFinishedSemaphore;
    std::unique_ptr<Vulkan::SubmitQueue> submitQueue;
    std::unique_ptr<Vulkan::PresentQueue> presentQueue;
    std::unique_ptr<Vulkan::Fence> presentFence;

    SDL_Window* handle = nullptr;
    std::vector<std::shared_ptr<Screen>> screens;
    int x = 100;
    int y = 100;
};
