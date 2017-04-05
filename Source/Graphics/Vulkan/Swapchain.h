#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"
#include "Surface.h"
#include "Image/ImageView.h"
#include <vector>

namespace Vulkan {

class Swapchain : public Handle<VkSwapchainKHR>, public Devicer {

public:
    Swapchain(const Device* device, const Surface* surface);
    ~Swapchain();
    void create() override;
    void destroy() override;
    VkImage getImage(int i) const { return images.at(i); }
    VkImageView getImageView(int i) const { return imageViews.at(i)->getHandle(); }
    int getImageCount() const { return images.size(); }
    int getIndex() const { return index; }

    VkSwapchainCreateInfoKHR createInfo = {};

private:
    const Surface* surface;
    std::vector<VkImage> images;
    std::vector<std::shared_ptr<ImageView>> imageViews;
    int index = -1;
    static int indexCounter;
};

} // Vulkan
