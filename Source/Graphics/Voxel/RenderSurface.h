#pragma once
#include "../Drawable.h"
#include "../Graphics/OpenGL/ShaderGroup.h"
#include "../Graphics/OpenGL/Texture.h"
#include "../Graphics/OpenGL/VertexArray.h"
#include "../Graphics/OpenGL/Buffer.h"
#include <glm/glm.hpp>

class RenderSurface : public Drawable {

public:
    struct Ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    RenderSurface();
    void draw(float dt) override;

private:
    ShaderGroup* voxelShaderGroup;
    Texture texture;
    VertexArray vao;
    Buffer VBO;
    GLuint program;
};
