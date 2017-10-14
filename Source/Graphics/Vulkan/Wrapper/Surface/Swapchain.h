#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class Surface;

class Swapchain : public Handle<VkSwapchainKHR>, public Devicer {

public:
    Swapchain(Device* device, Surface* surface);
    ~Swapchain();
    void create() override;
    void destroy() override;

    size_t getCount() const { return images.size(); }
    VkImage getImage(size_t i) const { return images.at(i); }
    const std::vector<VkImage>& getImages() const { return images; }

    VkFormat getImageFormat() const { return createInfo.imageFormat; }

private:
    VkSwapchainCreateInfoKHR createInfo = {};
    Surface* surface;
    std::vector<VkImage> images;
};

} // Vulkan
