#pragma once
#include "Queue.h"
#include <vector>

namespace Vulkan {

class Swapchain;

class PresentQueue : public Queue {

public:
    PresentQueue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex = 0);
    void present();
    void addSwapchain(Swapchain* swapchain);
    void clearSwapchains();

private:
    VkPresentInfoKHR presentInfo = {};
    std::vector<VkSwapchainKHR> swapchainHandles;
    std::vector<Swapchain*> swapchains;
    std::vector<uint32_t> imageIndices;
};

} // Vulkan
