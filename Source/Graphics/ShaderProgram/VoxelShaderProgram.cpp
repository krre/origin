#include "VoxelShaderProgram.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"

VoxelShaderProgram::VoxelShaderProgram(const Vulkan::Device* device, Plane* plane) :
    plane(plane),
    ShaderProgram(device) {
    addShader("Shader/Voxel.vert.spv");
    addShader("Shader/Voxel.frag.spv");

    linkUniform("ubo", sizeof(ubo), &ubo);
    linkUniform("octree", MEMORY_SIZE);
    linkUniform("renderList", MAX_OCTREE_COUNT * sizeof(uint32_t));
    linkUniform("pickResult", sizeof(pickResult), &pickResult);
    linkUniform("debugOut", sizeof(debugOut), &debugOut);

    linkInput("position", plane->getVerticesSize(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, true);

    createResources();
}
