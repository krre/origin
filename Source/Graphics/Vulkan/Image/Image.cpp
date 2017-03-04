#include "Image.h"
#include "../Manager.h"

using namespace Vulkan;

Image::Image(const Device* device, uint32_t width, uint32_t height) :
    Devicer(device), memory(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    createInfo.imageType = VK_IMAGE_TYPE_2D;
    createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    createInfo.extent.width = width;
    createInfo.extent.height = height;
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
    VkResult result = checkError(vkCreateImage(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create image");

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device->getHandle(), handle, &memRequirements);
    memory.setMemoryTypeIndex(device->getPhysicalDevice()->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    memory.allocate(memRequirements.size);

    vkBindImageMemory(device->getHandle(), handle, memory.getHandle(), 0);

    return result;
}

void Image::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyImage(device->getHandle(), handle, nullptr))
}

void Image::setImageLayout(VkImageLayout imageLayout) {
    descriptorInfo.imageLayout = imageLayout;
}
