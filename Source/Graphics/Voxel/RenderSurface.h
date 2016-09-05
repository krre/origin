#pragma once
#include "../Drawable.h"
#include "../Graphics/OpenGL/ShaderGroup.h"
#include "../Graphics/OpenGL/Texture.h"
#include "../Graphics/OpenGL/VertexArray.h"
#include "../Graphics/OpenGL/Buffer.h"
#include <glm/glm.hpp>

constexpr int MAX_OCTREE_COUNT = 10;

class RenderSurface : public Drawable {

public:
    RenderSurface();
    void draw(float dt) override;

private:
    ShaderGroup* voxelShaderGroup;
    Texture objectsTexture;
    Texture octreesTexture;
    VertexArray vao;
    Buffer vbo;
    Buffer objectsTbo;
    Buffer octreesTbo;
    GLuint program;
};
