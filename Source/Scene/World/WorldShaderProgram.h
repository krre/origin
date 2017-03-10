#pragma once
#include "../../Graphics/ShaderProgram.h"
#include <glm/glm.hpp>

class WorldShaderProgram : public ShaderProgram {

public:
    friend class WorldScene;

    struct UBO {
        int shadeless = 0;
        int pageBytes = PAGE_BYTES;
        int blockInfoEnd = BLOCK_INFO_END;
        int frameWidth;
        int frameHeight;
        int transformCount;

        float ambientStrength = 0.1;
        float lod;

        glm::vec4 backgroundColor = glm::vec4(0.77, 0.83, 0.83, 1.0);
        glm::vec4 lightColor;
        glm::vec4 lightPos;

        glm::vec4 pickPixel = glm::vec4(-1, -1, 0, 0);
    } ubo;

    struct Octree {
        uint32_t* data;
    } octree;

    struct RenderList {
        int count;
        uint32_t* offsets;
    } renderList;

    struct PickResult {
        glm::vec3 pos;
        uint32_t parent;
        uint32_t scale;
        int childIdx;
    } pickResult;

    struct DebugOut {
        glm::vec4 debugVec;
        int debugInt;
        float debugFloat;
    } debugOut;

    WorldShaderProgram(const Vulkan::Device* device);
};
