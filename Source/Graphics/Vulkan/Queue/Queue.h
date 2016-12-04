#pragma once
#include "../Base/CreatableObject.h"
#include "../Device.h"
#include <vector>

namespace Vulkan {

class Queue : public CreatableObject<VkQueue> {

public:
    Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    virtual void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores) = 0;
    bool create() override {}

protected:
    std::vector<VkSemaphore> waitSemaphores;

private:
    const Device* device;
};

} // Vulkan
