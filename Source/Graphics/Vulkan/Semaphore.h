#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class Semaphore : public VkObject {

public:
    Semaphore(const Device* device);
    ~Semaphore();
    VkSemaphore getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }

private:
    VkSemaphore handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
