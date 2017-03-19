#pragma once
#include "Queue.h"
#include <vector>

namespace Vulkan {

class PresentQueue : public Queue {

public:
    PresentQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    VkResult present();
    void addSwapchain(VkSwapchainKHR swapchain);
    uint32_t* getImageIndex(int i);

    VkPresentInfoKHR presentInfo = {};

private:
    std::vector<VkSwapchainKHR> swapchains;
    std::vector<uint32_t> imageIndices;
};

} // Vulkan
