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

    uint32_t width() const { return m_width; }
    uint32_t height() const { return m_height; }

    const Image* image() const { return m_image.get(); }
    const ImageView* imageView() const { return m_imageView.get(); }

private:
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    std::vector<unsigned char> m_data;
    std::unique_ptr<Image> m_image;
    std::unique_ptr<ImageView> m_imageView;
};

}
