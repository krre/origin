#include "CommandBuffer.h"
#include "../pipeline/Pipeline.h"

namespace Vulkan {

CommandBuffer::CommandBuffer(VkCommandBuffer handle) : Handle(handle) {
    m_beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
}

void CommandBuffer::addViewport(VkViewport viewport) {
    m_viewports.push_back(viewport);
}

void CommandBuffer::addScissor(VkRect2D scissor) {
    m_scissors.push_back(scissor);
}

void CommandBuffer::addVertexBuffer(VkBuffer vertexBuffer, VkDeviceSize offset) {
    m_vertexBuffers.push_back(vertexBuffer);
    m_vertexBufferOffsets.push_back(offset);
}

void CommandBuffer::clearVertexBuffers() {
    m_vertexBuffers.clear();
    m_vertexBufferOffsets.clear();
}

void CommandBuffer::addBufferCopy(VkBufferCopy bufferCopy) {
    m_bufferCopies.push_back(bufferCopy);
}

void CommandBuffer::addImageCopy(VkImageCopy imageCopy) {
    m_imageCopies.push_back(imageCopy);
}

void CommandBuffer::addBlitRegion(VkImageBlit blitRegion) {
    m_blitRegions.push_back(blitRegion);
}

void CommandBuffer::addDynamicOffset(uint32_t dynamicOffset) {
    m_dynamicOffsets.push_back(dynamicOffset);
}

void CommandBuffer::addDescriptorSet(VkDescriptorSet descriptorSet) {
    m_descriptorSets.push_back(descriptorSet);
}

void CommandBuffer::clearDescriptorSets() {
    m_descriptorSets.clear();
}

VkMemoryBarrier CommandBuffer::createMemoryBarrier() {
    VkMemoryBarrier mb = {};
    mb.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;

    return mb;
}

void CommandBuffer::addMemoryBarrier(VkMemoryBarrier memoryBarrier) {
    m_memoryBarriers.push_back(memoryBarrier);
}

void CommandBuffer::clearMemoryBarriers() {
    m_memoryBarriers.clear();
}

VkBufferMemoryBarrier CommandBuffer::createBufferMemoryBarrier() {
    VkBufferMemoryBarrier bmb = {};
    bmb.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    bmb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    bmb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    return bmb;
}

void CommandBuffer::addBufferMemoryBarrier(VkBufferMemoryBarrier bufferMemoryBarrier) {
    m_bufferMemoryBarriers.push_back(bufferMemoryBarrier);
}

void CommandBuffer::clearBufferMemoryBarriers() {
    m_bufferMemoryBarriers.clear();
}

void CommandBuffer::addImageMemoryBarrier(VkImageMemoryBarrier imageMemoryBarrier) {
    m_imageMemoryBarriers.push_back(imageMemoryBarrier);
}

void CommandBuffer::clearImageMemoryBarriers() {
    m_imageMemoryBarriers.clear();
}

void CommandBuffer::clear() {
    m_viewports.clear();
    m_scissors.clear();
    m_vertexBuffers.clear();
    m_vertexBufferOffsets.clear();
    m_bufferCopies.clear();
    m_imageCopies.clear();
    m_blitRegions.clear();
    m_dynamicOffsets.clear();
    m_descriptorSets.clear();
    m_memoryBarriers.clear();
    m_bufferMemoryBarriers.clear();
    m_imageMemoryBarriers.clear();
}

VkImageMemoryBarrier CommandBuffer::createImageMemoryBarrier() {
    VkImageMemoryBarrier imb = {};
    imb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    imb.subresourceRange = {};
    imb.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imb.subresourceRange.levelCount = 1;
    imb.subresourceRange.layerCount = 1;

    return imb;
}


void CommandBuffer::begin(VkCommandBufferUsageFlags flags) {
    m_beginInfo.flags = flags;
    VULKAN_CHECK_RESULT(vkBeginCommandBuffer(m_handle, &m_beginInfo), "Failed to begin command buffer");
}

void CommandBuffer::end() {
    VULKAN_CHECK_RESULT(vkEndCommandBuffer(m_handle), "Failed to end command buffer");
}

void CommandBuffer::beginRenderPass(VkRenderPassBeginInfo* renderPassBeginInfo, VkSubpassContents contents) {
    vkCmdBeginRenderPass(m_handle, renderPassBeginInfo, contents);
}

void CommandBuffer::endRenderPass() {
    vkCmdEndRenderPass(m_handle);
}

void CommandBuffer::pipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) {
    vkCmdPipelineBarrier(m_handle, srcStageMask, dstStageMask, dependencyFlags,
                         m_memoryBarriers.size(), m_memoryBarriers.data(),
                         m_bufferMemoryBarriers.size(), m_bufferMemoryBarriers.data(),
                         m_imageMemoryBarriers.size(), m_imageMemoryBarriers.data());
}

void CommandBuffer::setViewport(uint32_t firstViewport) {
    assert(!m_viewports.empty());
    vkCmdSetViewport(m_handle, firstViewport, m_viewports.size(), m_viewports.data());
}

void CommandBuffer::setScissor(uint32_t firstScissor) {
    assert(!m_scissors.empty());
    vkCmdSetScissor(m_handle, firstScissor, m_scissors.size(), m_scissors.data());
}

void CommandBuffer::bindPipeline(Pipeline* pipeline) {
    vkCmdBindPipeline(m_handle, pipeline->bindPoint(), pipeline->handle());
}

void CommandBuffer::bindVertexBuffers(uint32_t firstBinding) {
    assert(!m_vertexBuffers.empty());
    vkCmdBindVertexBuffers(m_handle, firstBinding, m_vertexBuffers.size(), m_vertexBuffers.data(), m_vertexBufferOffsets.data());
    m_vertexBuffers.clear();
    m_vertexBufferOffsets.clear();
}

void CommandBuffer::bindIndexBuffer(VkBuffer buffer, VkIndexType indexType, VkDeviceSize offset) {
    vkCmdBindIndexBuffer(m_handle, buffer, offset, indexType);
}

void CommandBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer) {
    assert(!m_bufferCopies.empty());
    vkCmdCopyBuffer(m_handle, srcBuffer, dstBuffer, m_bufferCopies.size(), m_bufferCopies.data());
}

void CommandBuffer::blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter) {
    assert(!m_blitRegions.empty());
    vkCmdBlitImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, m_blitRegions.size(), m_blitRegions.data(), filter);
}

void CommandBuffer::copyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout) {
    assert(!m_imageCopies.empty());
    vkCmdCopyImage(m_handle, srcImage, srcImageLayout, dstImage, dstImageLayout, m_imageCopies.size(), m_imageCopies.data());
}

void CommandBuffer::drawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
    vkCmdDrawIndexed(m_handle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

void CommandBuffer::draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    vkCmdDraw(m_handle, vertexCount, instanceCount, firstVertex, firstInstance);
}

void CommandBuffer::drawIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    vkCmdDrawIndirect(m_handle, buffer, offset, drawCount, stride);
}

void CommandBuffer::bindDescriptorSets(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t firstSet) {
    vkCmdBindDescriptorSets(m_handle, bindPoint, layout, firstSet, m_descriptorSets.size(), m_descriptorSets.data(), m_dynamicOffsets.size(), m_dynamicOffsets.data());
    m_descriptorSets.clear();
    m_dynamicOffsets.clear();
}

void CommandBuffer::setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask) {
    VkImageMemoryBarrier imageMemoryBarrier = createImageMemoryBarrier();
    imageMemoryBarrier.oldLayout = oldImageLayout;
    imageMemoryBarrier.newLayout = newImageLayout;
    imageMemoryBarrier.image = image;
    imageMemoryBarrier.subresourceRange.aspectMask = aspectMask;

    switch (oldImageLayout) {
        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_PREINITIALIZED:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
            break;

        default:
            break;
    }

    switch (newImageLayout) {
        case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            break;

        case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            break;

        case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;

        case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            break;

        default:
            break;
    }

    clearImageMemoryBarriers();
    addImageMemoryBarrier(imageMemoryBarrier);
    pipelineBarrier(srcStageMask, dstStageMask);
}

void CommandBuffer::reset() {
    clear();
    vkResetCommandBuffer(m_handle, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
}

}
