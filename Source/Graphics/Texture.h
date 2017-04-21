#pragma once
#include "Core/Object.h"
#include <vector>
#include <vulkan/vulkan.h>

namespace Vulkan {
    class ImageView;
    class Image;
}


class Texture : public Object {

public:
    Texture(const std::string& path, VkFormat format = VK_FORMAT_R8G8B8A8_UNORM);
    uint32_t getWidth() const;
    uint32_t getHeight() const;
    const Vulkan::Image* getImage() const { return image.get(); }
    const Vulkan::ImageView* getImageView() const { return imageView.get(); }

private:
    std::vector<unsigned char> data;
    std::unique_ptr<Vulkan::Image> image;
    std::shared_ptr<Vulkan::ImageView> imageView;
};
