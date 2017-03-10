#include "WorldShaderProgram.h"

WorldShaderProgram::WorldShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Voxel.vert.spv");
    addShader("Shader/Voxel.frag.spv");

    linkBuffer("ubo", &ubo, sizeof(ubo));
    linkBuffer("pickResult", &pickResult, sizeof(pickResult));
    linkBuffer("debugOut", &debugOut, sizeof(debugOut));

    createDescriptors();
}
