#pragma once
#include "../Core/Object.h"
#include "Vulkan/Image/ImageView.h"
#include "Vulkan/Image/Image.h"
#include <vector>

class Texture : public Object {

public:
    Texture(const std::string& path, VkFormat format = VK_FORMAT_R8G8B8A8_UNORM);
    uint32_t getWidth() const { return image.getWidth(); }
    uint32_t getHeight() const { return image.getHeight(); }
    const Vulkan::Image& getImage() const { return image; }
    const Vulkan::ImageView* getImageView() const { return imageView.get(); }

private:
    std::vector<unsigned char> data;
    Vulkan::Image image;
    std::shared_ptr<Vulkan::ImageView> imageView;
};
