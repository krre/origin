#pragma once
#include "../base/Collection.h"
#include "../device/Devicer.h"

namespace Vulkan {

class CommandPool;

class CommandBuffers : public Collection<VkCommandBuffer>, public Devicer {
public:
    CommandBuffers(Device* device, CommandPool* commandPool, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
    ~CommandBuffers();

    void allocate(uint32_t count);
    void destroy() override;

private:
    VkCommandBufferAllocateInfo m_allocateInfo = {};
    CommandPool* m_commandPool = nullptr;
};

}
