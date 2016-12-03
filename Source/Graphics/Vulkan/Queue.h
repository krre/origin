#pragma once
#include "CreatableObject.h"
#include "Device.h"
#include <vector>

namespace Vulkan {

class Queue : public CreatableObject<VkQueue> {

public:
    Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    bool create() override {}
    void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores, bool submit);
    void setSignalSemaphores(std::vector<VkSemaphore> signalSemaphores);
    void setWaitDstStageMask(std::vector<VkPipelineStageFlags> waitDstStageMask);

    void setCommandBuffers(std::vector<VkCommandBuffer> commandBuffers);
    void setCommandBuffersCount(uint32_t count);
    void setCommandBuffersData(const VkCommandBuffer* data);
    bool submit();

    bool present();
    void setSwapchains(std::vector<VkSwapchainKHR> swapchains);
    void setImageIndices(const uint32_t* indices);

private:
    const Device* device;
    VkSubmitInfo submitInfo = {};
    std::vector<VkSemaphore> submitWaitSemaphores;
    std::vector<VkSemaphore> presentWaitSemaphores;
    std::vector<VkSemaphore> signalSemaphores;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkPipelineStageFlags> waitDstStageMask;

    VkPresentInfoKHR presentInfo = {};
    std::vector<VkSwapchainKHR> swapchains;

};

} // Vulkan
