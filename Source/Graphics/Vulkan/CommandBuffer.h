#pragma once
#include "VkObject.h"
#include "Device.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffer : public VkObject {

public:
    CommandBuffer(const Device* device);
    bool isValid() const { return handle != VK_NULL_HANDLE; }
    VkCommandBuffer getHandle() const { return handle; }
    void allocate(const CommandPool* commandPool, int count);
    int getCount() const { return commandBuffers.size(); }

private:
    VkCommandBuffer handle = VK_NULL_HANDLE;
    const Device* device;
    std::vector<VkCommandBuffer> commandBuffers;
};

} // Vulkan
