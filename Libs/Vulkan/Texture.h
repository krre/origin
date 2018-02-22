#pragma once
#include <vector>
#include <memory>
#include <vulkan/vulkan.h>

namespace Vulkan {

class ImageView;
class Image;
class Device;

class Texture {

public:
    Texture(Device* device, uint32_t width, uint32_t height, void* data, VkDeviceSize size, VkDeviceSize offset = 0);
    ~Texture();
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }
    const Image* getImage() const { return image.get(); }
    const ImageView* getImageView() const { return imageView.get(); }

private:
    uint32_t width = 0;
    uint32_t height = 0;
    std::vector<unsigned char> data;
    std::unique_ptr<Image> image;
    std::unique_ptr<ImageView> imageView;
};

} // Origin
