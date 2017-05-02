#pragma once
#include <memory>
#include <vulkan/vulkan.h>

namespace Vulkan {

class Device;
class CommandBuffers;
class CommandBuffer;

class CommandBufferOneTime {

public:
    CommandBufferOneTime(Device* device);
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
    Device* device;
    std::shared_ptr<CommandBuffers> commandBuffers;
    std::shared_ptr<CommandBuffer> commandBuffer;
};

} // Vulkan
