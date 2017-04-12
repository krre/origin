#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "Surface.h"
#include "Framebuffer.h"
#include "Image/ImageView.h"
#include "Queue/PresentQueue.h"
#include "Semaphore.h"
#include "RenderPass.h"
#include <vector>

namespace Vulkan {

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
    int getIndex() const { return index; }
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
