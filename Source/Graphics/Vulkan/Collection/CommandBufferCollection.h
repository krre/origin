#pragma once
#include "../Base/Collection.h"
#include "../Device.h"
#include "../CommandPool.h"

namespace Vulkan {

class CommandBufferCollection : public Collection<VkCommandBuffer> {

public:
    CommandBufferCollection(const Device* device, const CommandPool* commandPool);
    ~CommandBufferCollection();
    bool allocate(uint32_t count);

private:
    const Device* device;
    const CommandPool* commandPool;
    VkCommandBufferAllocateInfo allocateInfo = {};
};

} // Vulkan
