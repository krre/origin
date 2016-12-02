#pragma once
#include "VkCreatableObject.h"
#include "Device.h"

namespace Vulkan {

class Semaphore : public VkCreatableObject<VkSemaphore> {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    void create() override;

private:
    const Device* device;
    VkSemaphoreCreateInfo createInfo = {};
};

} // Vulkan
