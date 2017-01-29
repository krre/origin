#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class Queue : public Handle<VkQueue>, public Devicer {

public:
    Queue(const Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    virtual void setWaitSemaphores(std::vector<VkSemaphore> waitSemaphores) = 0;
    VkResult create() override {}
    void destroy() override {}

protected:
    std::vector<VkSemaphore> waitSemaphores;
};

} // Vulkan
