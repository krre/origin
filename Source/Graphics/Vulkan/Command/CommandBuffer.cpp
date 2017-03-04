#include "CommandBuffer.h"

using namespace Vulkan;

CommandBuffer::CommandBuffer(VkCommandBuffer handle) : Handle(handle) {
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
}

void CommandBuffer::addViewport(VkViewport viewport) {
    viewports.push_back(viewport);
}

VkResult CommandBuffer::begin(VkCommandBufferUsageFlags flags) {
    beginInfo.flags = flags;
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

void CommandBuffer::setViewport(uint32_t firstViewport) {
    vkCmdSetViewport(handle, firstViewport, viewports.size(), viewports.data());
}
