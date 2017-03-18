#include "CommandBuffer.h"

using namespace Vulkan;

CommandBuffer::CommandBuffer(VkCommandBuffer handle) : Handle(handle) {
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
}

void CommandBuffer::addViewport(VkViewport viewport) {
    viewports.push_back(viewport);
}

void CommandBuffer::addVertexBuffer(VkBuffer vertexBuffer, VkDeviceSize offset) {
    vertexBuffers.push_back(vertexBuffer);
    vertexBufferOffsets.push_back(offset);
}

VkResult CommandBuffer::begin(VkCommandBufferUsageFlags flags) {
    beginInfo.flags = flags;
    return checkError(vkBeginCommandBuffer(handle, &beginInfo), "Failed to begin command buffer");
}

VkResult CommandBuffer::end() {
    return checkError(vkEndCommandBuffer(handle), "Failed to end command buffer");
}

void CommandBuffer::beginRenderPass(const VkRenderPassBeginInfo* renderPassBeginInfo, VkSubpassContents contents) {
    vkCmdBeginRenderPass(handle, renderPassBeginInfo, contents);
}

void CommandBuffer::endRenderPass() {
    vkCmdEndRenderPass(handle);
}

void CommandBuffer::pipelineBarrier(PipelineBarrier* pipelineBarrier, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) {
    vkCmdPipelineBarrier(handle, srcStageMask, dstStageMask, dependencyFlags,
                         pipelineBarrier->getMemoryBarrierCount(), pipelineBarrier->getMemoryBarrierData(),
                         pipelineBarrier->getBufferMemoryBarrierCount(), pipelineBarrier->getBufferMemoryBarrierData(),
                         pipelineBarrier->getImageMemoryBarrierCount(), pipelineBarrier->getImageMemoryBarrierData());
}

void CommandBuffer::setViewport(uint32_t firstViewport) {
    assert(viewports.size() > 0);
    vkCmdSetViewport(handle, firstViewport, viewports.size(), viewports.data());
}

void CommandBuffer::bindPipeline(const Pipeline* pipeline) {
    vkCmdBindPipeline(handle, pipeline->getBindPoint(), pipeline->getHandle());
}
