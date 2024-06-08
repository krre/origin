#include "Image.h"
#include "../device/DeviceMemory.h"
#include "../device/PhysicalDevice.h"
#include <string.h>

namespace Vulkan {

Image::Image(Device* device) :
    Devicer(device) {
    m_memory = std::make_unique<DeviceMemory>(device);

    m_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    m_createInfo.imageType = VK_IMAGE_TYPE_2D;
    m_createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    m_createInfo.extent.depth = 1;
    m_createInfo.arrayLayers = 1;
    m_createInfo.mipLevels = 1;
    m_createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    m_createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    m_createInfo.tiling = VK_IMAGE_TILING_LINEAR;
    m_createInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
}

Image::Image(Device* device, VkImage image) :
        Devicer(device),
        Handle(image) {
}

Image::~Image() {
    destroy();
}

void Image::create() {
    VULKAN_CHECK_RESULT(vkCreateImage(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create image");

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(m_device->handle(), m_handle, &memRequirements);
    VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    if (m_createInfo.format == VK_FORMAT_D16_UNORM) {
        properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    }
    m_memory->setMemoryTypeIndex(m_device->physicalDevice()->findMemoryType(memRequirements.memoryTypeBits, properties));
    m_memory->allocate(memRequirements.size);

    vkBindImageMemory(m_device->handle(), m_handle, m_memory->handle(), 0);
}

void Image::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyImage(m_device->handle(), m_handle, nullptr))
}

void Image::setWidth(uint32_t width) {
    m_createInfo.extent.width = width;
}

void Image::setHeight(uint32_t height) {
    m_createInfo.extent.height = height;
}

void Image::setFormat(VkFormat format) {
    m_createInfo.format = format;
}

void Image::setUsage(VkImageUsageFlags usage) {
    m_createInfo.usage = usage;
}

void Image::setTiling(VkImageTiling tiling) {
    m_createInfo.tiling = tiling;
}

void Image::setInitialLayout(VkImageLayout initialLayout) {
    m_createInfo.initialLayout = initialLayout;
}

void Image::write(void* data, VkDeviceSize size, VkDeviceSize offset) {
    void* mapData;
    m_memory->map(&mapData, size, offset);
    memcpy(mapData, data, size);
    m_memory->unmap();
}

}
