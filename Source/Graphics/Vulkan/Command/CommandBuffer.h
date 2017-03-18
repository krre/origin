#pragma once
#include "../Base/Handle.h"
#include "../Device/Device.h"
#include "CommandPool.h"
#include "../Pipeline/PipelineBarrier.h"
#include <vector>

namespace Vulkan {

class CommandBuffer : public Handle<VkCommandBuffer> {

public:
    CommandBuffer(VkCommandBuffer handle);
    VkResult create() override {}
    void destroy() override {}
    void addViewport(VkViewport viewport);
    void addVertexBuffer(VkBuffer vertexBuffer, VkDeviceSize offset = 0);

    // Commands
    VkResult begin(VkCommandBufferUsageFlags flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);
    VkResult end();
    void beginRenderPass(const VkRenderPassBeginInfo* renderPassBeginInfo, VkSubpassContents contents = VK_SUBPASS_CONTENTS_INLINE);
    void endRenderPass();
    void pipelineBarrier(PipelineBarrier* pipelineBarrier, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags = 0);
    void setViewport(uint32_t firstViewport);
    void bindPipeline(const Pipeline* pipeline);
    void bindVertexBuffers(uint32_t firstBinding = 0);
    void bindIndexBuffer(VkBuffer buffer, VkIndexType indexType, VkDeviceSize offset = 0);

    VkCommandBufferBeginInfo beginInfo = {};

private:
    std::vector<VkViewport> viewports;
    std::vector<VkBuffer> vertexBuffers;
    std::vector<VkDeviceSize> vertexBufferOffsets;
};

} // Vulkan
