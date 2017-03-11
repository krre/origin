#include "TextShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

TextShaderProgram::TextShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Text.vert.spv");
    addShader("Shader/Text.frag.spv");

    createDescriptors();
}
