#pragma once
#include "Core/Object.h"
#include <vector>
#include <vulkan/vulkan.h>

namespace Origin {

namespace Vulkan {
    class ImageView;
    class Image;
}

class Texture : public Object {

public:
    Texture(const std::string& path);
    ~Texture();
    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }
    const Vulkan::Image* getImage() const { return image.get(); }
    const Vulkan::ImageView* getImageView() const { return imageView.get(); }

private:
    uint32_t width = 0;
    uint32_t height = 0;
    std::vector<unsigned char> data;
    std::unique_ptr<Vulkan::Image> image;
    std::unique_ptr<Vulkan::ImageView> imageView;
};

} // Origin
