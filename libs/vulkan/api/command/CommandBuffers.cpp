#include "CommandBuffers.h"
#include "CommandPool.h"
#include <assert.h>

namespace Vulkan {

CommandBuffers::CommandBuffers(Device* device, CommandPool* commandPool, VkCommandBufferLevel level) :
        Devicer(device), m_commandPool(commandPool) {
    m_allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    m_allocateInfo.level = level;
    m_allocateInfo.commandPool = commandPool->handle();
}

CommandBuffers::~CommandBuffers() {
    destroy();
}

void CommandBuffers::allocate(uint32_t count) {
    assert(m_collection.size() == 0 && count > 0);
    m_collection.resize(count);
    m_allocateInfo.commandBufferCount = count;

    VULKAN_CHECK_RESULT(vkAllocateCommandBuffers(m_device->handle(), &m_allocateInfo, m_collection.data()), "Failed to allocate command buffers");
}

void CommandBuffers::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeCommandBuffers(m_device->handle(), m_commandPool->handle(), m_collection.size(), m_collection.data()));
}

}
