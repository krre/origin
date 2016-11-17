#pragma once
#include "../Drawable.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include <glm/glm.hpp>

const int LOD_PIXEL_LIMIT = 1;

class RenderSurface : public Gagarin::Drawable {

struct DebugOut {
    glm::vec4 debugVec;
    int debugInt;
    float debugFloat;
};

public:
    RenderSurface();
    void draw(float dt) override;

private:
    ShaderGroup* raycastShaderGroup;
    ShaderGroup* voxelShaderGroup;
    ShaderGroup* surfaceShaderGroup;
    GLuint vao;
    GLuint vbo;
    GLuint surfaceTex;
    GLuint program;
    GLuint debugSsbo;
};
