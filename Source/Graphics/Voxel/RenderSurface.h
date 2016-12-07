#pragma once
#include "../Drawable.h"
#include <glm/glm.hpp>

const int LOD_PIXEL_LIMIT = 1;

class RenderSurface : public Gagarin::Drawable {

struct Octree {
    int octreeCount;
    uint octreeData[];
} octree;

struct PickResult {
    glm::vec3 pickPos;
    uint pickParent;
    uint pickScale;
    int pickChildIdx;
} pickResult;

struct RenderList {
    int renderCount;
    uint renderOffsets[];
} renderList;

struct DebugOut {
    glm::vec4 debugVec;
    int debugInt;
    float debugFloat;
} debugOut;

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
