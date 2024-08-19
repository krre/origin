#include "CommandBufferOneTime.h"
#include "CommandBuffers.h"
#include "CommandBuffer.h"
#include "../command/CommandPool.h"
#include "../Fence.h"
#include "../Queue.h"

namespace Vulkan {

CommandBufferOneTime::CommandBufferOneTime(Device* device, CommandPool* commandPool) :
        Devicer(device),
        m_commandPool(commandPool) {
    m_commandBuffers = std::make_unique<CommandBuffers>(device, commandPool);
    m_commandBuffers->allocate(1);
    m_commandBuffer = std::make_unique<CommandBuffer>(m_commandBuffers->at(0));
    m_commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
}

CommandBufferOneTime::~CommandBufferOneTime() {

}

void CommandBufferOneTime::apply() {
    m_commandBuffer->end();

    Fence fence(m_device);
    fence.create();

    Queue queue(m_device, m_commandPool->getQueueFamilyIndex(), 0);
    queue.addCommandBuffer(m_commandBuffer->handle());
    queue.submit(fence.handle());

    m_device->waitForFences({ fence.handle() });
}

void CommandBufferOneTime::blitImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, VkFilter filter) {
    m_commandBuffer->blitImage(srcImage, srcImageLayout, dstImage, dstImageLayout, filter);
}

void CommandBufferOneTime::copyImage(VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout) {
    m_commandBuffer->copyImage(srcImage, srcImageLayout, dstImage, dstImageLayout);
}

void CommandBufferOneTime::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer) {
    m_commandBuffer->copyBuffer(srcBuffer, dstBuffer);
}

void CommandBufferOneTime::setImageLayout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout oldImageLayout, VkImageLayout newImageLayout, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask) {
    m_commandBuffer->setImageLayout(image, aspectMask, oldImageLayout, newImageLayout, srcStageMask, dstStageMask);
}

void CommandBufferOneTime::addBlitRegion(VkImageBlit blitRegion) {
    m_commandBuffer->addBlitRegion(blitRegion);
}

void CommandBufferOneTime::addImageCopy(VkImageCopy imageCopy) {
    m_commandBuffer->addImageCopy(imageCopy);
}

void CommandBufferOneTime::addBufferCopy(VkBufferCopy bufferCopy) {
    m_commandBuffer->addBufferCopy(bufferCopy);
}

}
