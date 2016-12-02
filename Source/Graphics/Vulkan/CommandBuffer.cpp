#include "CommandBuffer.h"

using namespace Vulkan;

CommandBuffer::CommandBuffer(const Device* device) : device(device) {

}

void CommandBuffer::allocate(const CommandPool* commandPool, int count) {
    commandBuffers.resize(count);

    VkCommandBufferAllocateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.commandPool = commandPool->getHandle();
    info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    info.commandBufferCount = (uint32_t) commandBuffers.size();

    checkError(vkAllocateCommandBuffers(device->getHandle(), &info, commandBuffers.data()));
}
