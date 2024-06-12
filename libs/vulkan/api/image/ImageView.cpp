#include "ImageView.h"

namespace Vulkan {

ImageView::ImageView(Device* device, VkImage image) :
        Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    m_createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
    m_createInfo.image = image;
    m_createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    m_createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    m_createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    m_createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    m_createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    m_createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    m_createInfo.subresourceRange.baseMipLevel = 0;
    m_createInfo.subresourceRange.levelCount = 1;
    m_createInfo.subresourceRange.baseArrayLayer = 0;
    m_createInfo.subresourceRange.layerCount = 1;
}

ImageView::~ImageView() {
    vkDestroyImageView(m_device->handle(), m_handle, nullptr);
}

void ImageView::create() {
    VULKAN_CHECK_RESULT(vkCreateImageView(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create image view");
}

void ImageView::setFormat(VkFormat format) {
    m_createInfo.format = format;
}

void ImageView::setAspectMask(VkImageAspectFlags aspectMask) {
    m_createInfo.subresourceRange.aspectMask = aspectMask;
}

}
