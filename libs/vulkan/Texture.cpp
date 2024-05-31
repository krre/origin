#include "Texture.h"
#include "api/command/CommandBufferOneTime.h"
#include "api/image/ImageView.h"
#include "api/image/Image.h"
#include "api/device/PhysicalDevice.h"
#include "Renderer.h"

namespace Vulkan {

Texture::Texture(Device* device, uint32_t width, uint32_t height, void* data, VkDeviceSize size, VkDeviceSize offset) {
    m_image = std::make_unique<Image>(device);

    m_image->setWidth(width);
    m_image->setHeight(height);
    m_image->setFormat(VK_FORMAT_R8G8B8A8_UNORM);
    m_image->setUsage(VK_IMAGE_USAGE_SAMPLED_BIT);
    m_image->setInitialLayout(VK_IMAGE_LAYOUT_PREINITIALIZED);
    m_image->create();

    m_image->write(data, size, offset);

    m_imageView = std::make_unique<ImageView>(device, m_image->handle());
    m_imageView->setFormat(m_image->format());
    m_imageView->create();

    VkFormatProperties formatProps;
    vkGetPhysicalDeviceFormatProperties(device->physicalDevice()->handle(), VK_FORMAT_R8G8B8A8_UNORM, &formatProps);

    /* See if we can use a linear tiled image for a texture, if not, we will
     * need a staging image for the texture data */
    bool needStaging = (!(formatProps.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)) ? true : false;
    if (needStaging) {

    }

//    CommandBufferOneTime commandBuffer(device, Renderer::get()->getGraphicsCommandPool());
//    commandBuffer.setImageLayout(image->getHandle(), VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
//    commandBuffer.apply();
}

Texture::~Texture() {

}

}
