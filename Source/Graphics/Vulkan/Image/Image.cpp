#include "Image.h"
#include "../Manager.h"
#include <string.h>

using namespace Vulkan;

Image::Image(const Device* device) :
    Devicer(device), memory(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    createInfo.imageType = VK_IMAGE_TYPE_2D;
    createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    createInfo.extent.depth = 1;
    createInfo.arrayLayers = 1;
    createInfo.mipLevels = 1;
    createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    createInfo.tiling = VK_IMAGE_TILING_LINEAR;
    createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
}

Image::~Image() {
    destroy();
}

VkResult Image::create() {
    CHECK_RESULT(vkCreateImage(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create image");

    vkGetImageMemoryRequirements(device->getHandle(), handle, &memRequirements);
    memory.setMemoryTypeIndex(device->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    memory.allocate(memRequirements.size);

    vkBindImageMemory(device->getHandle(), handle, memory.getHandle(), 0);
}

void Image::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyImage(device->getHandle(), handle, nullptr))
}

void Image::setWidth(uint32_t width) {
    createInfo.extent.width = width;
}

void Image::setHeight(uint32_t height) {
    createInfo.extent.height = height;
}

void Image::setFormat(VkFormat format) {
    createInfo.format = format;
}

void Image::setUsage(VkImageUsageFlags usage) {
    createInfo.usage = usage;
}

void Image::setInitialLayout(VkImageLayout initialLayout) {
    createInfo.initialLayout = initialLayout;
}

void Image::write(void* data, VkDeviceSize count, VkDeviceSize offset) {
    void* mapData;
    memory.map(memRequirements.size, offset, &mapData);
    memcpy(mapData, data, count);
    memory.unmap();
}
