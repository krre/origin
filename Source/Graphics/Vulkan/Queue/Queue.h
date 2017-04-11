#pragma once
#include "../Base/Handle.h"
#include "../Device/Devicer.h"
#include <vector>

namespace Vulkan {

class Queue : public Handle<VkQueue>, public Devicer {

public:
    Queue(uint32_t queueFamilyIndex, uint32_t queueIndex, Device* device = nullptr);
    void addWaitSemaphore(VkSemaphore semaphore);
    void setWaitSemaphore(VkSemaphore semaphore);
    void create() override {}
    void destroy() override {}

protected:
    std::vector<VkSemaphore> waitSemaphores;
};

} // Vulkan
