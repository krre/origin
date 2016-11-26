#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class CommandPool : public VkObject {

public:
    CommandPool(const Device* device);
    ~CommandPool();
    VkCommandPool getHandle() const { return handle; }
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    bool reset();

private:
    VkCommandPool handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
