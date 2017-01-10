#include "PipelineBarrier.h"

using namespace Vulkan;

PipelineBarrier::PipelineBarrier() {

}

VkMemoryBarrier PipelineBarrier::createMemoryBarrier() {
    VkMemoryBarrier mb = {};
    mb.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;

    return mb;
}

void PipelineBarrier::addMemoryBarrier(VkMemoryBarrier memoryBarrier) {
    memoryBarriers.push_back(memoryBarrier);
}

void PipelineBarrier::clearMemoryBarriers() {
    memoryBarriers.clear();
}

VkBufferMemoryBarrier PipelineBarrier::createBufferMemoryBarrier() {
    VkBufferMemoryBarrier bmb = {};
    bmb.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    bmb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    bmb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

    return bmb;
}

void PipelineBarrier::addBufferMemoryBarrier(VkBufferMemoryBarrier bufferMemoryBarrier) {
    bufferMemoryBarriers.push_back(bufferMemoryBarrier);
}

void PipelineBarrier::clearBufferMemoryBarriers() {
    bufferMemoryBarriers.clear();
}

void PipelineBarrier::addImageMemoryBarrier(VkImageMemoryBarrier imageMemoryBarrier) {
    imageMemoryBarriers.push_back(imageMemoryBarrier);
}

void PipelineBarrier::clearImageMemoryBarriers() {
    imageMemoryBarriers.clear();
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
