#include "BaseShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

BaseShaderProgram::BaseShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Base.vert.spv");
    addShader("Shader/Base.frag.spv");

    linkBuffer("uboVert", sizeof(uboVert), &uboVert);
    linkBuffer("uboFrag", sizeof(uboFrag), &uboFrag);

    createDescriptors();
}
