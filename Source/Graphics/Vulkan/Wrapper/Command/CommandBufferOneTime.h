#pragma once
#include "Graphics/Vulkan/Wrapper/Device/Devicer.h"
#include <memory>

namespace Origin {

namespace Vulkan {

class Device;
class CommandBuffers;
class CommandBuffer;
class CommandPool;

class CommandBufferOneTime : Devicer {

public:
    CommandBufferOneTime(Device* device, CommandPool* commandPool);
    ~CommandBufferOneTime();
    void setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask);
    void addBlitRegion(VkImageBlit blitRegion);
    void addImageCopy(VkImageCopy imageCopy);
    void addBufferCopy(VkBufferCopy bufferCopy);
    void apply();

    // Commands
    void blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter = VK_FILTER_NEAREST);
    void copyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer);

private:
    std::unique_ptr<CommandBuffers> commandBuffers;
    std::unique_ptr<CommandBuffer> commandBuffer;
    CommandPool* commandPool;
};

} // Vulkan

} // Origin

