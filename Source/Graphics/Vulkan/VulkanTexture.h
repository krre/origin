#pragma once
#include "Graphics/Texture.h"
#include <vector>
#include <vulkan/vulkan.h>

namespace Origin {

namespace Vulkan {
    class ImageView;
    class Image;
}

class VulkanTexture : public Texture {

public:
    VulkanTexture(const std::string& path);
    ~VulkanTexture();
    const Vulkan::Image* getImage() const { return image.get(); }
    const Vulkan::ImageView* getImageView() const { return imageView.get(); }

private:
    std::vector<unsigned char> data;
    std::unique_ptr<Vulkan::Image> image;
    std::unique_ptr<Vulkan::ImageView> imageView;
};

} // Origin
