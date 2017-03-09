#include "WorldShaderProgram.h"

WorldShaderProgram::WorldShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Voxel.vert.spv");
    addShader("Shader/Voxel.frag.spv");
    createDescriptors();
}
