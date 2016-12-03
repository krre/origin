#pragma once
#include "../CreatableObject.h"
#include "../Device.h"
#include <vector>

namespace Vulkan {

class Queue : public CreatableObject<VkQueue> {

public:
    Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    bool create() override {}
    virtual void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores) {}
    void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores, bool submit);

    bool present();
    void setSwapchains(std::vector<VkSwapchainKHR> swapchains);
    void setImageIndices(const uint32_t* indices);

protected:
    std::vector<VkSemaphore> waitSemaphores;

private:
    const Device* device;
    std::vector<VkSemaphore> presentWaitSemaphores;

    VkPresentInfoKHR presentInfo = {};
    std::vector<VkSwapchainKHR> swapchains;

};

} // Vulkan
