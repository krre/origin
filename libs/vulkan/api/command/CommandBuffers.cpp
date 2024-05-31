#include "CommandBuffers.h"
#include "CommandPool.h"
#include <assert.h>

namespace Vulkan {

CommandBuffers::CommandBuffers(Device* device, CommandPool* commandPool, VkCommandBufferLevel level) :
        Devicer(device), commandPool(commandPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = level;
    allocateInfo.commandPool = commandPool->handle();
}

CommandBuffers::~CommandBuffers() {
    destroy();
}

void CommandBuffers::allocate(uint32_t count) {
    assert(collection.size() == 0 && count > 0);
    collection.resize(count);
    allocateInfo.commandBufferCount = count;

    VULKAN_CHECK_RESULT(vkAllocateCommandBuffers(m_device->handle(), &allocateInfo, collection.data()), "Failed to allocate command buffers");
}

void CommandBuffers::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeCommandBuffers(m_device->handle(), commandPool->handle(), collection.size(), collection.data()));
}

}
