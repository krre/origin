#pragma once
#include "Graphics/Vulkan/Base/Collection.h"
#include "Graphics/Vulkan/Device/Devicer.h"

namespace Vulkan {

class CommandPool;

class CommandBuffers : public Collection<VkCommandBuffer>, public Devicer {

public:
    CommandBuffers(const CommandPool* commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, Device* device = nullptr);
    ~CommandBuffers();
    bool allocate(uint32_t count);
    void destroy() override;

private:
    VkCommandBufferAllocateInfo allocateInfo = {};
    const CommandPool* commandPool;
};

} // Vulkan
