#pragma once
#include "Queue.h"
#include <vector>

namespace Vulkan {

class PresentQueue : public Queue {

public:
    PresentQueue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    bool create() override;
    void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores) override;

    bool present();
    void setSwapchains(std::vector<VkSwapchainKHR> swapchains);
    void setImageIndices(const uint32_t* indices);

private:
    VkPresentInfoKHR presentInfo = {};
    std::vector<VkSwapchainKHR> swapchains;
};

} // Vulkan
