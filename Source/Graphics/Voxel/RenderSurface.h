#pragma once
#include "../Drawable.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include <glm/glm.hpp>

constexpr int MAX_OCTREE_COUNT = 10;
constexpr int OBJECT_STRIDE = 8;

class RenderSurface : public Drawable {

public:
    RenderSurface();
    void draw(float dt) override;
    void sendOctreeToGPU(int offset, const std::vector<uint32_t>& data);

private:
    ShaderGroup* voxelShaderGroup;
    GLuint objectsTexture;
    GLuint octreesTexture;
    GLuint vao;
    GLuint vbo;
    GLuint objectsTbo;
    GLuint octreesTbo;
    GLuint program;
};
