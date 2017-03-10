#include "VoxelShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

VoxelShaderProgram::VoxelShaderProgram(const Vulkan::Device* device) : ShaderProgram(device) {
    addShader("Shader/Voxel.vert.spv");
    addShader("Shader/Voxel.frag.spv");

    linkBuffer("ubo", &ubo, sizeof(ubo));
    linkBuffer("octree", &octree, MEMORY_SIZE);
    linkBuffer("renderList", &renderList, MAX_OCTREE_COUNT * sizeof(uint32_t));
    linkBuffer("pickResult", &pickResult, sizeof(pickResult));
    linkBuffer("debugOut", &debugOut, sizeof(debugOut));

    createDescriptors();
}
