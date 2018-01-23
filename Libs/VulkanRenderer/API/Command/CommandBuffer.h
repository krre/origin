#pragma once
#include "../Base/Handle.h"
#include <vector>

namespace Vulkan {

class Pipeline;

class CommandBuffer : public Handle<VkCommandBuffer> {

public:
    CommandBuffer(VkCommandBuffer handle);
    void create() override {}
    void destroy() override {}
    void addViewport(VkViewport viewport);
    void addScissor(VkRect2D scissor);
    void addVertexBuffer(VkBuffer vertexBuffer, VkDeviceSize offset = 0);
    void addBufferCopy(VkBufferCopy bufferCopy);
    void addImageCopy(VkImageCopy imageCopy);
    void addBlitRegion(VkImageBlit blitRegion);
    void addDynamicOffset(uint32_t dynamicOffset);
    void addDescriptorSet(VkDescriptorSet descriptorSet);

    static VkMemoryBarrier createMemoryBarrier();
    void addMemoryBarrier(VkMemoryBarrier memoryBarrier);
    void clearMemoryBarriers();

    static VkBufferMemoryBarrier createBufferMemoryBarrier();
    void addBufferMemoryBarrier(VkBufferMemoryBarrier bufferMemoryBarrier);
    void clearBufferMemoryBarriers();

    static VkImageMemoryBarrier createImageMemoryBarrier();
    void addImageMemoryBarrier(VkImageMemoryBarrier imageMemoryBarrier);
    void clearImageMemoryBarriers();

    // Commands
    void begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);
    void end();
    void reset();
    void beginRenderPass(VkRenderPassBeginInfo* renderPassBeginInfo, VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE);
    void endRenderPass();
    void pipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags = 0);
    void setViewport(uint32_t firstViewport);
    void setScissor(uint32_t firstScissor);
    void bindPipeline(Pipeline* pipeline);
    void bindVertexBuffers(uint32_t firstBinding = 0);
    void bindIndexBuffer(VkBuffer buffer, VkIndexType indexType, VkDeviceSize offset = 0);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer);
    void blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter = VK_FILTER_NEAREST);
    void copyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout);
    void drawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
    void bindDescriptorSets(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t firstSet = 0);
    void setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask);

private:
    VkCommandBufferBeginInfo beginInfo = {};
    std::vector<VkViewport> viewports;
    std::vector<VkRect2D> scissors;
    std::vector<VkBuffer> vertexBuffers;
    std::vector<VkDeviceSize> vertexBufferOffsets;
    std::vector<VkBufferCopy> bufferCopies;
    std::vector<VkImageCopy> imageCopies;
    std::vector<VkImageBlit> blitRegions;
    std::vector<uint32_t> dynamicOffsets;
    std::vector<VkDescriptorSet> descriptorSets;

    std::vector<VkMemoryBarrier> memoryBarriers;
    std::vector<VkBufferMemoryBarrier> bufferMemoryBarriers;
    std::vector<VkImageMemoryBarrier> imageMemoryBarriers;
};

} // Vulkan
