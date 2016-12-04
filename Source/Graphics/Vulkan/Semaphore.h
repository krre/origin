#pragma once
#include "Base/CreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Semaphore : public CreatableObject<VkSemaphore> {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    bool create() override;

private:
    const Device* device;
    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan
