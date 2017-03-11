#include "TextShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

TextShaderProgram::TextShaderProgram(const Vulkan::Device* device) :
    ShaderProgram(device),
    sampler(device),
    samplerImage(device),
    samplerImageView(device) {
    addShader("Shader/Text.vert.spv");
    addShader("Shader/Text.frag.spv");

    sampler.create();

    samplerImage.createInfo.extent.width = 100;
    samplerImage.createInfo.extent.height = 100;
    samplerImage.createInfo.format = VK_FORMAT_R8_UNORM;
    samplerImage.createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
//    samplerImage.createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
//    samplerImage.createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    samplerImage.create();

    samplerImageView.createInfo.image = samplerImage.getHandle();
    samplerImageView.createInfo.format = samplerImage.createInfo.format;
    samplerImageView.createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    samplerImageView.createInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B,	VK_COMPONENT_SWIZZLE_A };
    samplerImageView.createInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    samplerImageView.create();

    VkDescriptorImageInfo descriptorImageInfo = {};
    descriptorImageInfo.sampler = sampler.getHandle();
    descriptorImageInfo.imageView = samplerImage.getHandle();
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    linkImage("samplerFont", descriptorImageInfo);

    createDescriptors();
}
