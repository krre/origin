#include "TextShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"
#include "../../Resource/ResourceManager.h"

TextShaderProgram::TextShaderProgram(const Vulkan::Device* device) :
    ShaderProgram(device),
    sampler(device) {

    addShader("Shader/Text.vert.spv");
    addShader("Shader/Text.frag.spv");

    font = ResourceManager::get()->load<Font>("Fonts/inconsolata.fnt");

    sampler.create();

    VkDescriptorImageInfo descriptorImageInfo = {};
    descriptorImageInfo.sampler = sampler.getHandle();
    descriptorImageInfo.imageView = font->getTexture()->getImageView()->getHandle();
    descriptorImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;

    linkImage("samplerFont", descriptorImageInfo);

    createResources();
}
