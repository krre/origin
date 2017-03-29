#pragma once
#include "CommandBuffers.h"
#include "CommandBuffer.h"

namespace Vulkan {

class CommandBufferOneTime {

public:
    CommandBufferOneTime(Device* device);
    void apply();

    void begin() { commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT); }
    void end() { commandBuffer->end(); }
    void setImageLayout(VkImage image, VkImageAspectFlags aspectMask,
                        VkImageLayout oldImageLayout, VkImageLayout newImageLayout,
                        VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask) {
        commandBuffer->setImageLayout(image, aspectMask, oldImageLayout, newImageLayout, srcStageMask, dstStageMask);
    }
    void addBlitRegion(VkImageBlit blitRegion) { commandBuffer->addBlitRegion(blitRegion); }

private:
    Device* device;
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
};

} // Vulkan
