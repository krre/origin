#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffers : public Collection<VkCommandBuffer> {

public:
    CommandBuffers(const Device* device, const CommandPool* commandPool);
    ~CommandBuffers();
    bool allocate(uint32_t count);

private:
    const Device* device;
    const CommandPool* commandPool;
    VkCommandBufferAllocateInfo allocateInfo = {};
};

} // Vulkan
