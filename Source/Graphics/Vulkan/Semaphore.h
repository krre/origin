#pragma once
#include "Base/Handle.h"
#include "Device/Device.h"

namespace Vulkan {

class Semaphore : public Handle<VkSemaphore> {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    VkResult create() override;
    void destroy() override;

private:
    const Device* device;
    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan
