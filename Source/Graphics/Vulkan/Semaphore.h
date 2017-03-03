#pragma once
#include "Base/Handle.h"
#include "Device/Devicer.h"

namespace Vulkan {

class Semaphore : public Handle<VkSemaphore>, public Devicer {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    VkResult create() override;
    void destroy() override;

    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan
