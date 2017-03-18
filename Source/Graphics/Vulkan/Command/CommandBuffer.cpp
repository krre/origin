#include "CommandBuffer.h"

using namespace Vulkan;

CommandBuffer::CommandBuffer(VkCommandBuffer handle) : Handle(handle) {
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
}

void CommandBuffer::addViewport(VkViewport viewport) {
    viewports.push_back(viewport);
}

void CommandBuffer::addScissor(VkRect2D scissor) {
    scissors.push_back(scissor);
}

void CommandBuffer::addVertexBuffer(VkBuffer vertexBuffer, VkDeviceSize offset) {
    vertexBuffers.push_back(vertexBuffer);
    vertexBufferOffsets.push_back(offset);
}

void CommandBuffer::addCopyRegion(VkBufferCopy copyRegion) {
    copyRegions.push_back(copyRegion);
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

void CommandBuffer::setScissor(uint32_t firstScissor) {
    assert(scissors.size() > 0);
    vkCmdSetScissor(handle, firstScissor, scissors.size(), scissors.data());
}

void CommandBuffer::bindPipeline(const Pipeline* pipeline) {
    vkCmdBindPipeline(handle, pipeline->getBindPoint(), pipeline->getHandle());
}

void CommandBuffer::bindVertexBuffers(uint32_t firstBinding) {
    assert(vertexBuffers.size() > 0);
    vkCmdBindVertexBuffers(handle, firstBinding, vertexBuffers.size(), vertexBuffers.data(), vertexBufferOffsets.data());
}

void CommandBuffer::bindIndexBuffer(VkBuffer buffer, VkIndexType indexType, VkDeviceSize offset) {
    vkCmdBindIndexBuffer(handle, buffer, offset, indexType);
}

void CommandBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer) {
    assert(copyRegions.size() > 0);
    vkCmdCopyBuffer(handle, srcBuffer, dstBuffer, copyRegions.size(), copyRegions.data());
}
