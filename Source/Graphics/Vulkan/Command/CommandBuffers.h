#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffers : public Collection<VkCommandBuffer> {

public:
    CommandBuffers(const Device* device, const CommandPool* commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    ~CommandBuffers();
    bool allocate(uint32_t count);

private:
    const Device* device;
    const CommandPool* commandPool;
    VkCommandBufferAllocateInfo allocateInfo = {};
};

} // Vulkan
