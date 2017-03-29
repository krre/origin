#pragma once
#include "CommandBuffers.h"
#include "CommandBuffer.h"

namespace Vulkan {

class CommandBufferOneTime {

public:
    CommandBufferOneTime(Device* device);
    void setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask);
    void addBlitRegion(VkImageBlit blitRegion);
    void addImageCopy(VkImageCopy imageCopy);
    void apply();

    // Commands
    void begin();
    void end();
    void blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter = VK_FILTER_NEAREST);

private:
    Device* device;
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
};

} // Vulkan
