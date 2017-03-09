#include "WorldShaderProgram.h"

WorldShaderProgram::WorldShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Voxel.vert.spv");
    addShader("Shader/Voxel.frag.spv");

    link("ubo", &ubo, sizeof(ubo));
    link("pickResult", &pickResult, sizeof(pickResult));
    link("debugOut", &debugOut, sizeof(debugOut));

    createDescriptors();
}
