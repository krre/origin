#pragma once
#include "Device/Devicer.h"

namespace Vulkan {

class Semaphore : public Devicer<VkSemaphore> {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    VkResult create() override;
    void destroy() override;

private:
    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan
