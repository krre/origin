#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Handle.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"
#include <vector>

namespace Origin {

namespace Vulkan {

class Semaphore;
class Fence;

class Queue : public Handle<VkQueue>, public Devicer {

public:
    Queue(Device* device, uint32_t queueFamilyIndex, uint32_t queueIndex);
    void create() override {}
    void destroy() override {}
    void addWaitSemaphore(Semaphore* semaphore);
    void clearWaitSemaphores();
    void waitIdle();
    void syncHost(Fence* fence);

protected:
    std::vector<VkSemaphore> waitSemaphores;
};

} // Vulkan

} // Origin
