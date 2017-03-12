#include "TextShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"
#include "../../Resource/ResourceManager.h"

TextShaderProgram::TextShaderProgram(const Vulkan::Device* device) :
    ShaderProgram(device),
    sampler(device),
    samplerImage(device),
    samplerImageView(device) {

    addShader("Shader/Text.vert.spv");
    addShader("Shader/Text.frag.spv");

    font = ResourceManager::get()->load<Font>("Fonts/inconsolata.fnt");

    sampler.create();

    samplerImage.createInfo.extent.width = 1;
    samplerImage.createInfo.extent.height = 1;
    samplerImage.createInfo.format = VK_FORMAT_R8_UNORM;
    samplerImage.createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    samplerImage.createInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED; // TODO: Better VK_IMAGE_LAYOUT_GENERAL
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

    font->uploadTexture(samplerImage.getMemory());
}
