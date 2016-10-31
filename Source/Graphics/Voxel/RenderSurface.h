#pragma once
#include "../Drawable.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include <glm/glm.hpp>

class RenderSurface : public Drawable {

struct DebugOut {
    int debugInt;
    float debugFloat;
    glm::vec4 debugVec;
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
