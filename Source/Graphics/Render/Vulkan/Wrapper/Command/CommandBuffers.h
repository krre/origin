#pragma once
#include "Graphics/Render/Vulkan/Wrapper/Base/Collection.h"
#include "Graphics/Render/Vulkan/Wrapper/Device/Devicer.h"

namespace Vulkan {

class CommandPool;

class CommandBuffers : public Collection<VkCommandBuffer>, public Devicer {

public:
    CommandBuffers(const CommandPool* commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, Device* device = nullptr);
    ~CommandBuffers();
    void allocate(uint32_t count);
    void destroy() override;

private:
    VkCommandBufferAllocateInfo allocateInfo = {};
    const CommandPool* commandPool;
};

} // Vulkan
