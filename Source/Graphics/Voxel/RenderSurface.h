#pragma once
#include "../Drawable.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include <glm/glm.hpp>

class RenderSurface : public Drawable {

public:
    RenderSurface();
    void draw(float dt) override;

private:
    ShaderGroup* voxelShaderGroup;
    ShaderGroup* raycastShaderGroup;
    GLuint vao;
    GLuint vbo;
    GLuint program;
};
