#pragma once
#include "../Scene3D.h"
#include "../../Graphics/ShaderProgram.h"
#include "../../ECS/Entity.h"
#include "../../UI/Viewport.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"
#include "../../Graphics/Vulkan/Buffer.h"
#include "../../Graphics/Plane.h"
#include <SDL.h>
#include <glm/glm.hpp>

const int LOD_PIXEL_LIMIT = 1;

class Console;

class WorldScene : public Scene3D {

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

public:
    WorldScene();
    ~WorldScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void pause() override;
    void resume() override;
    EntityId getCharacterId() { return characterId; }
    uint64_t getSeed() { return seed; }
    void setSeed(uint64_t seed);

private:
    void create();
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void onKeyPressed(const SDL_KeyboardEvent& event) override;

    std::shared_ptr<Vulkan::Buffer> vertexBuffer;
    std::shared_ptr<Console> console;
    EntityId characterId;
    uint64_t seed;
    Viewport viewport;
    Plane plane;
    ShaderProgram shaderProgram;
};
