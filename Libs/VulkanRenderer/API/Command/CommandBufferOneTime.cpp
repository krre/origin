#include "CommandBufferOneTime.h"
#include "CommandBuffers.h"
#include "CommandBuffer.h"
#include "../Command/CommandPool.h"
#include "../Fence.h"
#include "../Queue.h"

namespace Vulkan {

CommandBufferOneTime::CommandBufferOneTime(Device* device, CommandPool* commandPool) :
        Devicer(device),
        commandPool(commandPool) {
    commandBuffers = std::make_unique<CommandBuffers>(device, commandPool);
    commandBuffers->allocate(1);
    commandBuffer = std::make_unique<CommandBuffer>(commandBuffers->at(0));
    commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
}

CommandBufferOneTime::~CommandBufferOneTime() {

}

void CommandBufferOneTime::apply() {
    commandBuffer->end();

    Fence fence(device);
    fence.create();

    Queue queue(device, commandPool->getQueueFamilyIndex(), 0);
    queue.addCommandBuffer(commandBuffer->getHandle());
    queue.submit(&fence);

    device->waitForFences({ fence.getHandle() });
}

void CommandBufferOneTime::blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter) {
    commandBuffer->blitImage(srcImage, srcImageLayout, dstImage, dstImageLayout, filter);
}

void CommandBufferOneTime::copyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout) {
    commandBuffer->copyImage(srcImage, srcImageLayout, dstImage, dstImageLayout);
}

void CommandBufferOneTime::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer) {
    commandBuffer->copyBuffer(srcBuffer, dstBuffer);
}

void CommandBufferOneTime::setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask) {
    commandBuffer->setImageLayout(image, aspectMask, oldImageLayout, newImageLayout, srcStageMask, dstStageMask);
}

void CommandBufferOneTime::addBlitRegion(VkImageBlit blitRegion) {
    commandBuffer->addBlitRegion(blitRegion);
}

void CommandBufferOneTime::addImageCopy(VkImageCopy imageCopy) {
    commandBuffer->addImageCopy(imageCopy);
}

void CommandBufferOneTime::addBufferCopy(VkBufferCopy bufferCopy) {
    commandBuffer->addBufferCopy(bufferCopy);
}

} // Vulkan
