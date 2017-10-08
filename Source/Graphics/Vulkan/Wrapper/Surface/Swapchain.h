#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class Surface;
class Framebuffer;
class Semaphore;
class ImageView;
class PresentQueue;
class RenderPass;

class Swapchain : public Handle<VkSwapchainKHR>, public Devicer {

public:
    Swapchain(const Surface* surface, Device* device = nullptr);
    ~Swapchain();
    void create() override;
    void destroy() override;
    VkImage getImage(int i) const { return images.at(i); }
    Framebuffer* getFramebuffer(int i) { return framebuffers.at(i).get(); }
    VkFormat getImageFormat() const { return createInfo.imageFormat; }
    int getCount() const { return images.size(); }
    void saveImage(const std::string& filePath);
    void acquireNextImage();
    Semaphore* getImageAvailableSemaphore() const { return imageAvailableSemaphore.get(); }
    PresentQueue* getPresentQueue() const { return presentQueue.get(); }
    RenderPass* getRenderPass() const { return renderPass.get(); }
    void rebuild();

private:
    VkSwapchainCreateInfoKHR createInfo = {};
    const Surface* surface;
    std::vector<VkImage> images;
    std::vector<std::shared_ptr<Framebuffer>> framebuffers;
    std::vector<std::shared_ptr<ImageView>> imageViews;
    std::shared_ptr<Semaphore> imageAvailableSemaphore;
    std::shared_ptr<PresentQueue> presentQueue;
    std::shared_ptr<RenderPass> renderPass;
    int index = -1;
    static int indexCounter;
};

} // Vulkan
