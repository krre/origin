#include "VoxelShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

VoxelShaderProgram::VoxelShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Voxel.vert.spv");
    addShader("Shader/Voxel.frag.spv");

    linkUniform("ubo", &ubo, sizeof(ubo));
    linkUniform("octree", &octree, MEMORY_SIZE);
    linkUniform("renderList", &renderList, MAX_OCTREE_COUNT * sizeof(uint32_t));
    linkUniform("pickResult", &pickResult, sizeof(pickResult));
    linkUniform("debugOut", &debugOut, sizeof(debugOut));

    createDescriptors();
}
