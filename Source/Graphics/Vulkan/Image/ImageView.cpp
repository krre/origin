#include "ImageView.h"

using namespace Vulkan;

ImageView::ImageView(const Device* device, const Surface* surface, VkImage image) :
    device(device),
    surface(surface) {
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = image;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = surface->getFormat(0).format;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;
}

ImageView::~ImageView() {
    destroy();
}

VkResult ImageView::create() {
    return checkError(vkCreateImageView(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create image view");
}

void ImageView::destroy() {
    VULKAN_DESTROY_HANDLE(vkDestroyImageView(device->getHandle(), handle, nullptr))
}
