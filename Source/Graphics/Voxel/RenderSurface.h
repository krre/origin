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
    struct Ray {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    RenderSurface();
    void draw(float dt) override;
    void sendDataToGPU();

private:
    ShaderGroup* voxelShaderGroup;
    Texture octreeToWorldTexture;
    VertexArray vao;
    Buffer vbo;
    Buffer tbo;
    GLuint program;
};
