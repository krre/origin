#pragma once
#include "../Base/Collection.h"
#include "../Device/Devicer.h"
#include "CommandPool.h"

namespace Vulkan {

class CommandBuffers : public Collection<VkCommandBuffer>, public Devicer {

public:
    CommandBuffers(const Device* device, const CommandPool* commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    ~CommandBuffers();
    bool allocate(uint32_t count);
    void destroy() override;

private:
    VkCommandBufferAllocateInfo allocateInfo = {};
    const CommandPool* commandPool;
};

} // Vulkan
