#pragma once
#include "Queue.h"
#include <vector>

namespace Vulkan {

class PresentQueue : public Queue {

public:
    PresentQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    VkResult present();
    void setSwapchains(std::vector<VkSwapchainKHR> swapchains);

    VkPresentInfoKHR presentInfo = {};

private:
    std::vector<VkSwapchainKHR> swapchains;
};

} // Vulkan
