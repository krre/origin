#include "BaseShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

BaseShaderProgram::BaseShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Base.vert.spv");
    addShader("Shader/Base.frag.spv");

    linkUniform("uboVert", &uboVert, sizeof(uboVert));
    linkUniform("uboFrag", &uboFrag, sizeof(uboFrag));

    createDescriptors();
}
