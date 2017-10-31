#pragma once
#include "Graphics/Vulkan/Base/Handle.h"
#include "Graphics/Vulkan/Device/Devicer.h"
#include <vector>

namespace Vulkan {

class Semaphore;
class Fence;

class Queue : public Handle<VkQueue>, public Devicer {

public:
    Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    void create() override {}
    void destroy() override {}
    void addWaitSemaphore(Semaphore* semaphore);
    void waitIdle();
    void syncHost(Fence* fence);

protected:
    std::vector<VkSemaphore> waitSemaphores;
};

} // Vulkan
