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

    struct AABB {
        glm::vec3 min;
        glm::vec3 max;
    };

    RenderSurface();
    void draw(float dt) override;

private:
    ShaderGroup* voxelShaderGroup;
    Texture texture;
    VertexArray VAO;
    Buffer VBO;
};
