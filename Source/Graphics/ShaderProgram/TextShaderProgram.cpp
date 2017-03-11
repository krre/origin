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
    samplerImage.create();

    samplerImageView.createInfo.image = samplerImage.getHandle();
    samplerImageView.createInfo.format = samplerImage.createInfo.format;
    samplerImageView.create();

    VkDescriptorImageInfo descriptorImageInfo = {};
    descriptorImageInfo.sampler = sampler.getHandle();
    descriptorImageInfo.imageView = samplerImageView.getHandle();
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    linkImage("samplerFont", descriptorImageInfo);

    createDescriptors();
}
