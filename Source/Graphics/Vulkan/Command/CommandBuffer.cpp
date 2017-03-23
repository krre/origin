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

void CommandBuffer::addBlitRegion(VkImageBlit blitRegion) {
    blitRegions.push_back(blitRegion);
}

void CommandBuffer::addDynamicOffset(uint32_t dynamicOffset) {
    dynamicOffsets.push_back(dynamicOffset);
}

void CommandBuffer::addDescriptorSet(VkDescriptorSet descriptorSet) {
    descriptorSets.push_back(descriptorSet);
}

VkMemoryBarrier CommandBuffer::createMemoryBarrier() {
    VkMemoryBarrier mb = {};
    mb.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;

    return mb;
}

void CommandBuffer::addMemoryBarrier(VkMemoryBarrier memoryBarrier) {
    memoryBarriers.push_back(memoryBarrier);
}

void CommandBuffer::clearMemoryBarriers() {
    memoryBarriers.clear();
}

VkBufferMemoryBarrier CommandBuffer::createBufferMemoryBarrier() {
    VkBufferMemoryBarrier bmb = {};
    bmb.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    bmb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    bmb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    return bmb;
}

void CommandBuffer::addBufferMemoryBarrier(VkBufferMemoryBarrier bufferMemoryBarrier) {
    bufferMemoryBarriers.push_back(bufferMemoryBarrier);
}

void CommandBuffer::clearBufferMemoryBarriers() {
    bufferMemoryBarriers.clear();
}

void CommandBuffer::addImageMemoryBarrier(VkImageMemoryBarrier imageMemoryBarrier) {
    imageMemoryBarriers.push_back(imageMemoryBarrier);
}

void CommandBuffer::clearImageMemoryBarriers() {
    imageMemoryBarriers.clear();
}

VkImageMemoryBarrier CommandBuffer::createImageMemoryBarrier() {
    VkImageMemoryBarrier imb = {};
    imb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    imb.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imb.subresourceRange.baseMipLevel = 0;
    imb.subresourceRange.levelCount = 1;
    imb.subresourceRange.layerCount = 1;

    return imb;
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

void CommandBuffer::pipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) {
    vkCmdPipelineBarrier(handle, srcStageMask, dstStageMask, dependencyFlags,
                         memoryBarriers.size(), memoryBarriers.data(),
                         bufferMemoryBarriers.size(), bufferMemoryBarriers.data(),
                         imageMemoryBarriers.size(), imageMemoryBarriers.data());
}

void CommandBuffer::setViewport(uint32_t firstViewport) {
    assert(!viewports.empty());
    vkCmdSetViewport(handle, firstViewport, viewports.size(), viewports.data());
}

void CommandBuffer::setScissor(uint32_t firstScissor) {
    assert(!scissors.empty());
    vkCmdSetScissor(handle, firstScissor, scissors.size(), scissors.data());
}

void CommandBuffer::bindPipeline(const Pipeline* pipeline) {
    vkCmdBindPipeline(handle, pipeline->getBindPoint(), pipeline->getHandle());
}

void CommandBuffer::bindVertexBuffers(uint32_t firstBinding) {
    assert(!vertexBuffers.empty());
    vkCmdBindVertexBuffers(handle, firstBinding, vertexBuffers.size(), vertexBuffers.data(), vertexBufferOffsets.data());
}

void CommandBuffer::bindIndexBuffer(VkBuffer buffer, VkIndexType indexType, VkDeviceSize offset) {
    vkCmdBindIndexBuffer(handle, buffer, offset, indexType);
}

void CommandBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer) {
    assert(!copyRegions.empty());
    vkCmdCopyBuffer(handle, srcBuffer, dstBuffer, copyRegions.size(), copyRegions.data());
}

void CommandBuffer::blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter) {
    assert(blitRegions.size());
    vkCmdBlitImage(handle, srcImage, srcImageLayout, dstImage, dstImageLayout, blitRegions.size(), blitRegions.data(), filter);
}

void CommandBuffer::drawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
    vkCmdDrawIndexed(handle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

void CommandBuffer::bindDescriptorSets(const Pipeline* pipeline, VkPipelineLayout layout, uint32_t firstSet) {
    vkCmdBindDescriptorSets(handle, pipeline->getBindPoint(), layout, firstSet, descriptorSets.size(), descriptorSets.data(), dynamicOffsets.size(), dynamicOffsets.data());
}
