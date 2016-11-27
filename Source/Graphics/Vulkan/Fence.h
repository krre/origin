#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class Fence : public VkObject {

public:
    Fence(const Device* device);
    ~Fence();
    VkFence getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkResult wait(uint32_t count);
    VkResult reset(uint32_t count);

private:
    VkFence handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
