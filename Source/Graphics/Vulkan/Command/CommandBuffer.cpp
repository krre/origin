#include "CommandBuffer.h"

using namespace Vulkan;

CommandBuffer::CommandBuffer(VkCommandBuffer handle) : Handle(handle) {
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
}

VkResult CommandBuffer::begin() {
    return checkError(vkBeginCommandBuffer(handle, &beginInfo), "Failed to begin command buffer");
}

VkResult CommandBuffer::end() {
    return checkError(vkEndCommandBuffer(handle), "Failed to end command buffer");
}
