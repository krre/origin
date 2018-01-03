#pragma once
#include "Graphics/Vulkan/Wrapper/Base/Collection.h"
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"

namespace Origin {

namespace Vulkan {

class CommandPool;

class CommandBuffers : public Collection<VkCommandBuffer>, public Devicer {

public:
    CommandBuffers(Device* device, CommandPool* commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    ~CommandBuffers();
    void allocate(uint32_t count);
    void destroy() override;

private:
    VkCommandBufferAllocateInfo allocateInfo = {};
    CommandPool* commandPool;
};

} // Vulkan

} // Origin
