#pragma once
#include "Base/Handle.h"
#include "Device.h"

namespace Vulkan {

class Semaphore : public Handle<VkSemaphore> {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    bool create() override;

private:
    const Device* device;
    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan
