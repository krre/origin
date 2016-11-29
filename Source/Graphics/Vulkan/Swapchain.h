#pragma once
#include "VkCreatableObject.h"
#include "Device.h"
#include "Surface.h"
#include <vector>

namespace Vulkan {

class Swapchain : public VkCreatableObject<VkSwapchainKHR> {

public:
    Swapchain(const Device* device, const Surface* surface);
    ~Swapchain();
    void create() override;
    VkImage getImage(int i) const { return images.at(i); }
    VkExtent2D getExtent() const { return extent; }
    int getCount() const { return images.size(); }

private:
    const Device* device;
    const Surface* surface;
    VkSwapchainCreateInfoKHR createInfo;
    std::vector<VkImage> images;
    VkExtent2D extent;
};

} // Vulkan
