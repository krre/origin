#include "WorldShaderProgram.h"

WorldShaderProgram::WorldShaderProgram() {
    addShader("Shader/Voxel.vert.spv");
//    addShader("Shader/Voxel.frag.spv");
    createDescriptors();
}
