#include "Texture.h"
#include "API/Command/CommandBufferOneTime.h"
#include "API/Image/ImageView.h"
#include "API/Image/Image.h"
#include "API/Device/PhysicalDevice.h"
#include "Renderer.h"

namespace Vulkan {

Texture::Texture(uint32_t width, uint32_t height, void* data, VkDeviceSize size, VkDeviceSize offset) {
    device = Renderer::get()->getGraphicsDevice();

    image = std::make_unique<Image>(device);

    image->setWidth(width);
    image->setHeight(height);
    image->setFormat(VK_FORMAT_R8G8B8A8_UNORM);
    image->setUsage(VK_IMAGE_USAGE_SAMPLED_BIT);
    image->setInitialLayout(VK_IMAGE_LAYOUT_PREINITIALIZED);
    image->create();

    image->write(data, size, offset);

    imageView = std::make_unique<ImageView>(device, image->getHandle());
    imageView->setFormat(image->getFormat());
    imageView->create();

    VkFormatProperties formatProps;
    vkGetPhysicalDeviceFormatProperties(device->getPhysicalDevice()->getHandle(), VK_FORMAT_R8G8B8A8_UNORM, &formatProps);

    /* See if we can use a linear tiled image for a texture, if not, we will
     * need a staging image for the texture data */
    bool needStaging = (!(formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)) ? true : false;
    if (needStaging) {

    }

    CommandBufferOneTime commandBuffer(device, Renderer::get()->getGraphicsCommandPool());
    commandBuffer.setImageLayout(image->getHandle(), VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
    commandBuffer.apply();
}

Texture::~Texture() {

}

} // Vulkan
