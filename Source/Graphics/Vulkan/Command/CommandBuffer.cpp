#include "CommandBuffer.h"

using namespace Vulkan;

CommandBuffer::CommandBuffer(VkCommandBuffer handle) : Handle(handle) {
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
}

void CommandBuffer::setFlags(VkCommandBufferUsageFlags flags) {
    beginInfo.flags = flags;
}

VkResult CommandBuffer::begin() {
    return checkError(vkBeginCommandBuffer(handle, &beginInfo), "Failed to begin command buffer");
}

VkResult CommandBuffer::end() {
    return checkError(vkEndCommandBuffer(handle), "Failed to end command buffer");
}

void CommandBuffer::pipelineBarrier(PipelineBarrier* pipelineBarrier, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) {
    vkCmdPipelineBarrier(handle, srcStageMask, dstStageMask, dependencyFlags,
                         pipelineBarrier->getMemoryBarrierCount(), pipelineBarrier->getMemoryBarrierData(),
                         pipelineBarrier->getBufferMemoryBarrierCount(), pipelineBarrier->getBufferMemoryBarrierData(),
                         pipelineBarrier->getImageMemoryBarrierCount(), pipelineBarrier->getImageMemoryBarrierData());
}
