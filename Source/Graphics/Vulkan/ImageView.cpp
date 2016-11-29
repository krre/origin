#include "ImageView.h"

using namespace Vulkan;

ImageView::ImageView(const Device* device, const SurfaceFormat* surfaceFormat, VkImage image) :
    device(device),
    surfaceFormat(surfaceFormat) {
    VkImageViewCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = image;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = surfaceFormat->getFormat(0).format;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    result = vkCreateImageView(device->getHandle(), &createInfo, nullptr, &handle);
}

ImageView::~ImageView() {
    if (handle != VK_NULL_HANDLE) {
        vkDestroyImageView(device->getHandle(), handle, nullptr);
    }
}
