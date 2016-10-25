#pragma once
#include "../Drawable.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include <glm/glm.hpp>

class RenderSurface : public Drawable {

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
};
