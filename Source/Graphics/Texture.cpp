#include "Texture.h"
#include <lodepng/lodepng.h>
#include "Vulkan/Manager.h"

Texture::Texture(const std::string& path, VkFormat format) :
    image(Vulkan::Manager::get()->getDevice()),
    imageView(Vulkan::Manager::get()->getDevice()) {
    lodepng::decode(data, image.createInfo.extent.width, image.createInfo.extent.height, path);
    image.createInfo.format = format;
    image.createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    image.createInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED; // TODO: Better VK_IMAGE_LAYOUT_GENERAL
//    samplerImage.createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    image.create();

    imageView.createInfo.image = image.getHandle();
    imageView.createInfo.format = image.createInfo.format;
    imageView.create();

    int size = image.createInfo.extent.width * image.createInfo.extent.height;
    void* mapData;
    image.getMemory()->map(size, 0, &mapData);
    memcpy(mapData, data.data(), size);
    image.getMemory()->unmap();
}
