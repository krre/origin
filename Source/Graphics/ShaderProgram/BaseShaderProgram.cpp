#include "BaseShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

BaseShaderProgram::BaseShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Base.vert.spv");
    addShader("Shader/Base.frag.spv");

    linkUniform("uboVert", sizeof(uboVert), &uboVert);
    linkUniform("uboFrag", sizeof(uboFrag), &uboFrag);

    createResources();
}
