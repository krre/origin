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
    samplerImage.create();

    samplerImageView.createInfo.image = samplerImage.getHandle();
    samplerImageView.createInfo.format = VK_FORMAT_R8_UNORM;
    samplerImageView.create();

//    samplerImage->descriptorInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
//    samplerImage->descriptorInfo.sampler = sampler.getHandle();
//    samplerImage->descriptorInfo.imageView = samplerImageView->getHandle();

//    samplerFont = new Vulkan::Descriptor(device, VK_SHADER_STAGE_FRAGMENT_BIT, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
//                                         VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0, MAX_CHAR_COUNT * sizeof(glm::vec4));
//    samplerFont->setImage(samplerImage);

    createDescriptors();
}
