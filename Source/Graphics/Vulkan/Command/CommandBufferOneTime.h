#pragma once
#include "CommandBuffers.h"
#include "CommandBuffer.h"

namespace Vulkan {

class CommandBufferOneTime {

public:
    CommandBufferOneTime(Device* device);
    void apply();

    void begin();
    void end();
    void setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask);
    void addBlitRegion(VkImageBlit blitRegion);

private:
    Device* device;
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
};

} // Vulkan
