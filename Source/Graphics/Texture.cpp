#include "Texture.h"
#include <lodepng/lodepng.h>
#include "Vulkan/Manager.h"

Texture::Texture(const std::string& path, VkFormat format) :
        image(Vulkan::Manager::get()->getDevice()) {
    uint32_t width;
    uint32_t height;
    lodepng::decode(data, width, height, path);

    image.setWidth(width);
    image.setHeight(height);
    image.setFormat(format);
    image.setUsage(VK_IMAGE_USAGE_SAMPLED_BIT);
    image.setInitialLayout(VK_IMAGE_LAYOUT_PREINITIALIZED);
    image.create();

    imageView = std::make_shared<Vulkan::ImageView>(Vulkan::Manager::get()->getDevice(), image.getHandle());
    imageView->createInfo.format = image.getFormat();
    imageView->create();

    void* mapData;
    image.getMemory()->map(image.memRequirements.size, 0, &mapData);
    memcpy(mapData, data.data(), data.size());
    image.getMemory()->unmap();
}
