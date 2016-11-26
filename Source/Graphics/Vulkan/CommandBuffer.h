#pragma once
#include "VkObject.h"
#include "Device.h"

namespace Vulkan {

class CommandBuffer : public VkObject {

public:
    CommandBuffer(const Device* device);
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkCommandBuffer getHandle() const { return handle; }

private:
    VkCommandBuffer handle = VK_NULL_HANDLE;
    const Device* device;
};

} // Vulkan
