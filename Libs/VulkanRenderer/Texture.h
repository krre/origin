#pragma once
#include <vector>
#include <memory>

namespace Vulkan {

class ImageView;
class Image;
class Device;

class Texture {

public:
    Texture(const std::string& path);
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
    Device* device;
};

} // Origin
