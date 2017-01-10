#include "PipelineBarrier.h"

using namespace Vulkan;

PipelineBarrier::PipelineBarrier() {

}

void PipelineBarrier::addMemoryBarrier(VkMemoryBarrier memoryBarrier) {
    memoryBarriers.push_back(memoryBarrier);
}

void PipelineBarrier::addBufferMemoryBarrier(VkBufferMemoryBarrier bufferMemoryBarrier) {
    bufferMemoryBarriers.push_back(bufferMemoryBarrier);
}

void PipelineBarrier::addImageMemoryBarrier(VkImageMemoryBarrier imageMemoryBarrier) {
    imageMemoryBarriers.push_back(imageMemoryBarrier);
}

VkImageMemoryBarrier PipelineBarrier::createImageMemoryBarrier() {
    VkImageMemoryBarrier imb = {};
    imb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    imb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    imb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    imb.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imb.subresourceRange.baseMipLevel = 0;
    imb.subresourceRange.levelCount = 1;
    imb.subresourceRange.layerCount = 1;

    return imb;
}
