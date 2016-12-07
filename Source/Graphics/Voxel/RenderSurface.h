#pragma once
#include "../Drawable.h"
#include <glm/glm.hpp>

const int LOD_PIXEL_LIMIT = 1;

class RenderSurface : public Gagarin::Drawable {

struct UBO {
    int pageBytes;
    int blockInfoEnd;

    int frameWidth;
    int frameHeight;

    glm::vec3 backgroundColor;
    glm::vec3 lightColor;
    glm::vec3 lightPos;
    bool shadeless;

    float ambientStrength;
    float lod;
    int transformCount;

    glm::vec2 pickPixel;
} ubo;

struct DebugOut {
    glm::vec4 debugVec;
    int debugInt;
    float debugFloat;
};

public:
    RenderSurface();
    void draw(float dt) override;

private:
//    ShaderGroup* raycastShaderGroup;
//    ShaderGroup* voxelShaderGroup;
//    ShaderGroup* surfaceShaderGroup;
//    GLuint vao;
//    GLuint vbo;
//    GLuint surfaceTex;
//    GLuint program;
//    GLuint debugSsbo;
};
